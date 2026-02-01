#!/usr/bin/env python3
"""
FFCC-Decomp Symbol Extraction Script
Extracts relevant symbol info from MAP files without loading massive files into context.
"""

import re
import sys
from pathlib import Path

def extract_symbols_for_function(map_file, function_name):
    """Extract symbol information for a specific function"""
    results = []
    
    try:
        with open(map_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                
                # Look for function symbols (contains the function name)
                if function_name in line:
                    # Try to parse common MAP file formats
                    # Format: address size section name
                    parts = line.split()
                    if len(parts) >= 4:
                        results.append({
                            'line': line_num,
                            'content': line,
                            'parsed': {
                                'address': parts[0] if parts[0].startswith('0x') else None,
                                'size': parts[1] if len(parts) > 1 else None,
                                'section': parts[2] if len(parts) > 2 else None,
                                'symbol': ' '.join(parts[3:]) if len(parts) > 3 else None
                            }
                        })
                    else:
                        results.append({
                            'line': line_num,
                            'content': line,
                            'parsed': None
                        })
                        
                # Stop after finding reasonable number of matches
                if len(results) >= 20:
                    break
                    
    except Exception as e:
        return [{'error': f"Failed to read {map_file}: {e}"}]
    
    return results

def extract_symbols_for_unit(map_file, unit_name):
    """Extract symbols for a source unit (e.g., all functions from a .cpp file)"""
    # Convert unit name to potential source file patterns
    source_patterns = []
    if '/' in unit_name:
        base_name = unit_name.split('/')[-1]
        source_patterns.extend([
            f"{base_name}.c",
            f"{base_name}.cpp", 
            f"{base_name}.s",
        ])
    
    results = []
    
    try:
        with open(map_file, 'r', encoding='utf-8', errors='ignore') as f:
            current_section = None
            for line_num, line in enumerate(f, 1):
                line_stripped = line.strip()
                
                # Track sections
                if line_stripped.startswith('.'):
                    current_section = line_stripped
                
                # Look for symbols related to our patterns
                for pattern in source_patterns:
                    if pattern in line:
                        results.append({
                            'line': line_num,
                            'section': current_section,
                            'content': line_stripped,
                            'pattern_match': pattern
                        })
                
                # Stop after reasonable number of matches
                if len(results) >= 50:
                    break
                    
    except Exception as e:
        return [{'error': f"Failed to read {map_file}: {e}"}]
    
    return results

def extract_section_info(map_file, section_name):
    """Extract section information and global variables"""
    results = []
    in_section = False
    
    try:
        with open(map_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line_stripped = line.strip()
                
                # Check if we're entering the target section
                if section_name in line_stripped and 'section layout' in line_stripped:
                    in_section = True
                    results.append({
                        'line': line_num,
                        'type': 'section_header',
                        'content': line_stripped
                    })
                    continue
                
                # If we're in the section, collect data until we hit another section
                if in_section:
                    # Stop at next section
                    if line_stripped.startswith('.') and 'section layout' in line_stripped and section_name not in line_stripped:
                        break
                    
                    # Skip empty lines
                    if not line_stripped:
                        continue
                    
                    # Parse data entries (address size virtual_addr flags section_type object_file)
                    parts = line_stripped.split()
                    if len(parts) >= 6 and parts[0] != section_name:
                        results.append({
                            'line': line_num,
                            'type': 'data_entry',
                            'content': line_stripped,
                            'parsed': {
                                'offset': parts[0],
                                'size': parts[1], 
                                'virtual_addr': parts[2],
                                'flags': parts[3],
                                'section': parts[4],
                                'object_file': parts[5]
                            }
                        })
                
                # Stop after reasonable number
                if len(results) >= 30:
                    break
                    
    except Exception as e:
        return [{'error': f"Failed to read {map_file}: {e}"}]
    
    return results

def extract_globals_for_file(map_file, object_file):
    """Extract global variables for a specific object file"""
    results = []
    
    try:
        with open(map_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line_stripped = line.strip()
                
                # Look for lines that reference our object file
                if object_file in line_stripped:
                    # Check if it's a data/bss entry (not .text)
                    parts = line_stripped.split()
                    if len(parts) >= 5 and (parts[4] == '.data' or parts[4] == '.bss' or parts[4] == '.sdata'):
                        results.append({
                            'line': line_num,
                            'content': line_stripped,
                            'section': parts[4],
                            'parsed': {
                                'offset': parts[0],
                                'size': parts[1],
                                'virtual_addr': parts[2],
                                'flags': parts[3],
                                'section': parts[4],
                                'symbol': ' '.join(parts[5:]) if len(parts) > 5 else 'unnamed'
                            }
                        })
                
                if len(results) >= 20:
                    break
                    
    except Exception as e:
        return [{'error': f"Failed to read {map_file}: {e}"}]
    
    return results

def extract_all_for_object(map_file, object_file):
    """Extract comprehensive information for a specific object file"""
    functions = []
    globals_data = []
    sections = []
    
    try:
        with open(map_file, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line_stripped = line.strip()
                
                # Look for lines that reference our object file (both PAL and EN formats)
                if (line_stripped.endswith(f"\t{object_file}") or 
                    line_stripped.endswith(f" {object_file}") or
                    f"found in {object_file}" in line_stripped):
                    
                    # Handle EN debug format: "symbol (type) found in object_file"
                    if "found in" in line_stripped:
                        parts = line_stripped.split()
                        if ') found in' in line_stripped:
                            symbol_part = line_stripped.split(') found in')[0]
                            if '(' in symbol_part:
                                symbol_name = symbol_part.split('(')[0].strip()
                                type_info = symbol_part.split('(')[1].strip() if '(' in symbol_part else 'unknown'
                            else:
                                symbol_name = symbol_part.strip()
                                type_info = 'unknown'
                        else:
                            symbol_name = parts[0] if parts else 'unnamed'
                            type_info = 'unknown'
                            
                        entry = {
                            'line': line_num,
                            'content': line_stripped,
                            'parsed': {
                                'flag': 'EN',
                                'offset': 'unknown',
                                'size': 'unknown', 
                                'virtual_addr': 'unknown',
                                'type_flag': type_info,
                                'symbol': symbol_name,
                                'object_file': object_file
                            }
                        }
                    # Handle PAL format: multiple patterns
                    elif line_stripped.strip().startswith('UNUSED'):
                        # UNUSED format: "UNUSED size ........ symbol object"
                        parts = line_stripped.split()
                        if len(parts) >= 5:
                            flag = 'UNUSED'
                            size = parts[1]
                            symbol = parts[3] if len(parts) > 3 else 'unnamed'
                            
                            entry = {
                                'line': line_num,
                                'content': line_stripped,
                                'parsed': {
                                    'flag': flag,
                                    'offset': 'UNUSED',
                                    'size': size,
                                    'virtual_addr': 'UNUSED',
                                    'type_flag': 'UNUSED',
                                    'symbol': symbol,
                                    'object_file': object_file
                                }
                            }
                        else:
                            entry = {'line': line_num, 'content': line_stripped, 'parsed': None}
                    elif 'UNUSED' in line_stripped and len(line_stripped.split()) >= 6:
                        # PAL UNUSED function: "G UNUSED size ........ symbol object"  
                        parts = line_stripped.split()
                        flag = parts[0]  # G
                        size = parts[2]
                        symbol = parts[4] if len(parts) > 4 else 'unnamed'
                        
                        entry = {
                            'line': line_num,
                            'content': line_stripped,
                            'parsed': {
                                'flag': flag,
                                'offset': 'UNUSED',
                                'size': size,
                                'virtual_addr': 'UNUSED',
                                'type_flag': 'UNUSED',
                                'symbol': symbol,
                                'object_file': object_file
                            }
                        }
                    else:
                        # Normal PAL format: "flag offset size addr type symbol \t object"  
                        parts = line_stripped.split()
                        if len(parts) >= 7:
                            flag = parts[0]  # G, X, etc.
                            offset = parts[1]
                            size = parts[2] 
                            virtual_addr = parts[3]
                            type_flag = parts[4]
                            symbol = parts[5]
                            
                            entry = {
                                'line': line_num,
                                'content': line_stripped,
                                'parsed': {
                                    'flag': flag,
                                    'offset': offset,
                                    'size': size,
                                    'virtual_addr': virtual_addr,
                                    'type_flag': type_flag,
                                    'symbol': symbol,
                                    'object_file': object_file
                                }
                            }
                        else:
                            # Fallback for unrecognized format
                            entry = {
                                'line': line_num,
                                'content': line_stripped,
                                'parsed': None
                            }
                        
                    # Categorize by type (handle both PAL and EN formats)
                    if entry.get('parsed'):
                        parsed = entry['parsed']
                        flag = parsed.get('flag', '')
                        type_flag = parsed.get('type_flag', '')
                        symbol = parsed.get('symbol', '')
                        
                        # Functions: PAL format (G+4 or G+UNUSED) or EN format (func in type)
                        if (flag == 'G' and (type_flag == '4' or type_flag == 'UNUSED')) or 'func' in type_flag:
                            functions.append(entry)
                        # Global data: multiple patterns
                        elif flag == 'UNUSED' or \
                             (type_flag == '4' and flag != 'G') or \
                             type_flag in ['.data', '.bss', '.sdata', '.sbss'] or \
                             'object' in type_flag or \
                             symbol.startswith('__RTTI__') or \
                             ('$' in symbol and not symbol.startswith('.')): # Constants like neg_one$206
                            globals_data.append(entry)
                        # Section headers
                        elif symbol in ['.data', '.bss', '.sdata', '.sbss', '.text'] or type_flag == '1':
                            sections.append(entry)
                        else:
                            sections.append(entry)  # Other symbols
                
                # Stop after reasonable number
                if len(functions) + len(globals_data) + len(sections) >= 50:
                    break
                    
    except Exception as e:
        return {'error': f"Failed to read {map_file}: {e}"}
    
    return {
        'functions': functions[:15],  # Limit each category
        'globals': globals_data[:15],
        'sections': sections[:10]
    }

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 extract_symbols.py <search_term> [context]")
        print("Examples:")
        print("  python3 extract_symbols.py pppMatrixXZY              # Function lookup")
        print("  python3 extract_symbols.py file.o                   # Everything for object")
        print("  python3 extract_symbols.py .data --section          # Section info")
        print("  python3 extract_symbols.py file.o --globals         # Globals in object")
        print("  python3 extract_symbols.py CMaterialEditor --globals # Globals containing term")
        return 1
    
    search_term = sys.argv[1]
    context = sys.argv[2] if len(sys.argv) > 2 else None
    
    repo_root = Path(__file__).parent
    pal_map = repo_root / "orig/GCCP01/game.MAP"
    en_map = repo_root / "orig/GCCE01/game.MAP"
    
    # Determine search mode
    is_section_search = context == "--section"
    is_globals_search = context == "--globals"
    is_object_file = search_term.endswith('.o') and not is_section_search and not is_globals_search
    
    print(f"SYMBOL SEARCH: {search_term}")
    if is_section_search:
        print("Mode: Section Information")
    elif is_globals_search:
        print("Mode: Global Variables")
    elif is_object_file:
        print("Mode: Comprehensive Object File Analysis")
    elif context:
        print(f"Unit context: {context}")
    print("=" * 60)
    
    # Execute appropriate search based on mode
    if is_object_file:
        # Comprehensive object file analysis - both PAL and EN
        if pal_map.exists():
            print(f"\n📦 PAL Release Analysis ({search_term}):")
            all_info = extract_all_for_object(pal_map, search_term)
            
            if 'error' in all_info:
                print(f"  Error: {all_info['error']}")
            else:
                # Functions
                if all_info['functions']:
                    print(f"\n  ⚡ Functions ({len(all_info['functions'])}):")
                    for i, func in enumerate(all_info['functions'], 1):
                        p = func['parsed']
                        try:
                            size_bytes = int(p['size'], 16) if p['size'] != 'UNUSED' else 0
                        except:
                            size_bytes = 0
                        size_kb = f"{size_bytes}"
                        print(f"    {i:2}. {p['symbol']} ({size_kb}b at {p['virtual_addr']})")
                
                # Global Variables
                if all_info['globals']:
                    print(f"\n  🌍 Global Variables ({len(all_info['globals'])}):")
                    for i, glob in enumerate(all_info['globals'], 1):
                        p = glob['parsed']
                        try:
                            size_bytes = int(p['size'], 16) if p['size'] != 'UNUSED' else 0
                        except:
                            size_bytes = 0
                        size_kb = f"{size_bytes:,}"
                        print(f"    {i:2}. {p['symbol']} ({size_kb}b {p['type_flag']} at {p['virtual_addr']})")
                
                # Other Sections
                if all_info['sections']:
                    print(f"\n  📂 Other Sections ({len(all_info['sections'])}):")
                    for i, sect in enumerate(all_info['sections'], 1):
                        p = sect['parsed']
                        print(f"    {i:2}. {p['symbol']} (type: {p['type_flag']})")
                
                # Summary
                total_functions = len(all_info['functions'])
                total_globals = len(all_info['globals'])
                print(f"\n  📊 Summary: {total_functions} functions, {total_globals} globals")
        
        # EN Debug analysis too
        if en_map.exists():
            print(f"\n📦 EN Debug Analysis ({search_term}):")
            all_info_en = extract_all_for_object(en_map, search_term)
            
            if 'error' in all_info_en:
                print(f"  Error: {all_info_en['error']}")
            else:
                # Functions
                if all_info_en['functions']:
                    print(f"\n  ⚡ Functions ({len(all_info_en['functions'])}):")
                    for i, func in enumerate(all_info_en['functions'], 1):
                        p = func['parsed']
                        try:
                            size_bytes = int(p['size'], 16) if p['size'] != 'UNUSED' else 0
                        except:
                            size_bytes = 0
                        size_kb = f"{size_bytes}"
                        print(f"    {i:2}. {p['symbol']} ({size_kb}b at {p['virtual_addr']})")
                
                # Summary
                total_functions_en = len(all_info_en['functions'])
                total_globals_en = len(all_info_en['globals'])
                print(f"\n  📊 Summary: {total_functions_en} functions, {total_globals_en} globals")
    
    elif is_section_search:
        # Section information search - both PAL and EN
        if pal_map.exists():
            print(f"\n📂 PAL Release Section Info ({search_term}):")
            section_results = extract_section_info(pal_map, search_term)
            
            if section_results:
                for i, result in enumerate(section_results[:8], 1):
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    elif result['type'] == 'section_header':
                        print(f"  📋 {result['content']}")
                    else:
                        print(f"  {i-1}. {result['content']}")
                        if result.get('parsed'):
                            p = result['parsed']
                            print(f"     Size: {p['size']} bytes at {p['virtual_addr']} from {p['object_file']}")
            else:
                print("  No section info found")
        
        if en_map.exists():
            print(f"\n📂 EN Debug Section Info ({search_term}):")
            section_results_en = extract_section_info(en_map, search_term)
            
            if section_results_en:
                for i, result in enumerate(section_results_en[:8], 1):
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    elif result['type'] == 'section_header':
                        print(f"  📋 {result['content']}")
                    else:
                        print(f"  {i-1}. {result['content']}")
                        if result.get('parsed'):
                            p = result['parsed']
                            print(f"     Size: {p['size']} bytes at {p['virtual_addr']} from {p['object_file']}")
            else:
                print("  No section info found")
    
    elif is_globals_search:
        # Globals search - both PAL and EN
        if pal_map.exists():
            print(f"\n🌍 PAL Release Global Variables (containing '{search_term}'):")
            if search_term.endswith('.o'):
                globals_results = extract_globals_for_file(pal_map, search_term)
            else:
                # Search for globals containing the term
                globals_results = extract_symbols_for_function(pal_map, search_term)
                globals_results = [r for r in globals_results if r.get('parsed') and 
                                 r['parsed'].get('section') in ['.data', '.bss', '.sdata']]
            
            if globals_results:
                for i, result in enumerate(globals_results[:8], 1):
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    else:
                        print(f"  {i}. {result['content']}")
                        if result.get('parsed'):
                            p = result['parsed'] 
                            section = p.get('section', 'unknown')
                            size = p.get('size', 'unknown')
                            addr = p.get('virtual_addr', 'unknown')
                            print(f"     {section} section: {size} bytes at {addr}")
            else:
                print("  No global variables found")
        
        if en_map.exists():
            print(f"\n🌍 EN Debug Global Variables (containing '{search_term}'):")
            if search_term.endswith('.o'):
                globals_results_en = extract_globals_for_file(en_map, search_term)
            else:
                # Search for globals containing the term
                globals_results_en = extract_symbols_for_function(en_map, search_term)
                globals_results_en = [r for r in globals_results_en if r.get('parsed') and 
                                     r['parsed'].get('section') in ['.data', '.bss', '.sdata']]
            
            if globals_results_en:
                for i, result in enumerate(globals_results_en[:8], 1):
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    else:
                        print(f"  {i}. {result['content']}")
                        if result.get('parsed'):
                            p = result['parsed'] 
                            section = p.get('section', 'unknown')
                            size = p.get('size', 'unknown')
                            addr = p.get('virtual_addr', 'unknown')
                            print(f"     {section} section: {size} bytes at {addr}")
            else:
                print("  No global variables found")
    
    else:
        # Function search (original behavior)
        if pal_map.exists():
            print("\n📍 PAL Release Symbols (GCCP01):")
            pal_results = extract_symbols_for_function(pal_map, search_term)
            
            if pal_results:
                for i, result in enumerate(pal_results[:5], 1):  # Limit to 5 results
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    else:
                        print(f"  {i}. Line {result['line']}: {result['content']}")
                        if result['parsed'] and result['parsed']['address']:
                            parsed = result['parsed']
                            print(f"     Address: {parsed['address']}, Size: {parsed['size']}, Section: {parsed['section']}")
            else:
                print("  No matches found")
        
        # Search EN MAP  
        if en_map.exists():
            print("\n📍 EN Debug Symbols (GCCE01):")
            en_results = extract_symbols_for_function(en_map, search_term)
            
            if en_results:
                for i, result in enumerate(en_results[:5], 1):  # Limit to 5 results
                    if 'error' in result:
                        print(f"  Error: {result['error']}")
                    else:
                        print(f"  {i}. Line {result['line']}: {result['content']}")
                        if result['parsed'] and result['parsed']['address']:
                            parsed = result['parsed']
                            print(f"     Address: {parsed['address']}, Size: {parsed['size']}, Section: {parsed['section']}")
            else:
                print("  No matches found")
    
    # Unit context search (for function mode only)
    if context and not is_section_search and not is_globals_search:
        print(f"\n📂 Unit Context ({context}):")
        if pal_map.exists():
            unit_results = extract_symbols_for_unit(pal_map, context)
            if unit_results[:3]:  # Show first 3 unit-related symbols
                for result in unit_results[:3]:
                    if 'error' not in result:
                        print(f"  {result['content']} (pattern: {result.get('pattern_match', 'unknown')})")
    
    print("\n⚠️  Note: Addresses and sizes are from a different build and may not match!")
    return 0

if __name__ == "__main__":
    exit(main())