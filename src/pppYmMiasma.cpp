#include "ffcc/pppYmMiasma.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>

extern int rand();

/*
 * --INFO--
 * Address:	80091234
 * Size:	872b
 */
void InitParticleData(VYmMiasma* vYmMiasma, _pppPObject* pppPObject, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    if (!particleData || !pYmMiasma) return;
    
    unsigned int randVal = rand();
    
    // Convert random value to normalized float (-1 to 1)
    double normalizedRand = (double)((float)((double)randVal / 4294967296.0) * 2.0 - 1.0);
    
    // Get particle color data index
    // Based on decompilation: access through pppEnvStPtr->m_particleColors array
    
    // Generate random direction values
    int randDir = rand();
    
    // Calculate angle-based direction using sin table (approximated)
    unsigned int angleIndex = (unsigned int)(normalizedRand * 16384.0f);  // Scale for sin table
    float sinVal = 0.0f;  // Placeholder - would use ppvSinTbl in real code
    float cosVal = 0.0f;  // Placeholder - would use ppvSinTbl in real code
    
    // Initialize velocity/direction in matrix format
    particleData->m_matrix[0][0] = cosVal;
    particleData->m_matrix[1][0] = cosVal;  // Duplicate for some reason
    particleData->m_matrix[0][1] = 0.0f;    // Y velocity component
    particleData->m_matrix[1][1] = 0.0f;    // Y velocity component
    particleData->m_matrix[0][2] = sinVal;
    particleData->m_matrix[1][2] = sinVal;  // Duplicate for some reason
    
    // Normalize velocity vector
    float velocityVecX = particleData->m_matrix[1][0];
    float velocityVecY = particleData->m_matrix[1][1]; 
    float velocityVecZ = particleData->m_matrix[1][2];
    // pppNormalize__FR3Vec3Vec would be called here
    
    // Set position based on world matrix if not in specific scene
    // if (Game.game.m_currentSceneId != 7) - scene check
    float worldPosX = 0.0f; // Would be pppMngStPtr->m_matrix[0][3]
    float worldPosY = 0.0f; // Would be pppMngStPtr->m_matrix[1][3]  
    float worldPosZ = 0.0f; // Would be pppMngStPtr->m_matrix[2][3]
    
    // Add velocity offset to world position
    particleData->m_matrix[0][3] = worldPosX + velocityVecX;
    particleData->m_matrix[1][3] = worldPosY + velocityVecY;
    particleData->m_matrix[2][3] = worldPosZ + velocityVecZ;
    
    // Set particle lifetime and age parameters
    // These use parameter offsets from the decompilation
    particleData->m_age = 60 + (randVal % 60);  // Approximate lifetime
    particleData->m_lifeTime = particleData->m_age;
    
    // Color initialization based on parameters
    particleData->m_colorDeltaAdd[0] = 1.0f;  // Would use *(float*)(param_3 + 0x34)
    
    // Y velocity calculation with randomization
    float baseVelocity = 1.0f;  // Would use *(float*)(param_3 + 0x10)
    float randomMultiplier = (float)normalizedRand * 0.5f;  // Would use param offset 0x14
    if ((unsigned int)normalizedRand & 1) {
        randomMultiplier *= -1.0f;
    }
    particleData->m_colorDeltaAdd[1] = baseVelocity + randomMultiplier;
    
    // Initialize size values
    particleData->m_sizeStart = 1.0f;
    particleData->m_sizeEnd = 0.1f; 
    particleData->m_sizeVal = particleData->m_sizeStart;
    
    // Direction tail initialization
    particleData->m_directionTail.x = 0;
    particleData->m_directionTail.y = 0;
    particleData->m_directionTail.z = (short)((int)randVal % 360);  // Random rotation
}

/*
 * --INFO--
 * Address:	80090e3c
 * Size:	1016b
 */
void UpdateParticleData(_pppPObject* pppPObject, _pppCtrlTable* pppCtrlTable, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    if (!particleData || !pYmMiasma) return;
    
    // Age the particle
    if (particleData->m_age > 0) {
        particleData->m_age--;
    }
    
    // Handle lifetime expiration - particle becomes inactive
    if (particleData->m_age <= 0) {
        // Mark particle as dead/inactive
        return;
    }
    
    // Update position using velocity stored in matrix
    // The velocity is stored in the matrix columns based on the init function
    float velocityX = particleData->m_matrix[1][0];
    float velocityY = particleData->m_matrix[1][1];
    float velocityZ = particleData->m_matrix[1][2];
    
    // Apply velocity to position
    particleData->m_matrix[0][3] += velocityX;
    particleData->m_matrix[1][3] += velocityY;
    particleData->m_matrix[2][3] += velocityZ;
    
    // Apply damping/friction to velocity
    particleData->m_matrix[1][0] *= 0.98f;  // X velocity damping
    particleData->m_matrix[1][1] -= 0.05f;  // Gravity on Y
    particleData->m_matrix[1][2] *= 0.98f;  // Z velocity damping
    
    // Update color/alpha fade based on age
    float ageRatio = (float)particleData->m_age / (float)particleData->m_lifeTime;
    
    // Size interpolation from start to end over lifetime
    particleData->m_sizeVal = particleData->m_sizeStart + 
        (particleData->m_sizeEnd - particleData->m_sizeStart) * (1.0f - ageRatio);
    
    // Update color components - fade out over time
    float fadeAmount = ageRatio * ageRatio;  // Quadratic fade for more realistic look
    
    // Apply color delta calculations
    // These would be more complex in the real implementation
    if (particleData->m_colorDeltaAdd[1] > 0.1f) {
        particleData->m_colorDeltaAdd[1] *= fadeAmount;
    }
    
    // Direction tail update for particle trail effect
    int tempZ = particleData->m_directionTail.z + 2;
    particleData->m_directionTail.z = (short)(tempZ % 360);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderParticle(_pppPObject* pppPObject, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    // Basic rendering setup
    if (!particleData) return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructYmMiasma(void)
{
    // Constructor stub
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2YmMiasma(void)
{
    // Secondary constructor stub
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructYmMiasma(void)
{
    // Destructor stub
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(void)
{
    // This function takes parameters but Ghidra shows them incorrectly
    // Based on the disassembly, it should receive:
    // pppYmMiasma*, control parameters, and context data
    
    if (!pppEnvStPtr) return;
    
    // For now, basic frame processing stub
    // The real implementation requires access to particle arrays
    // and complex memory management that needs the full context
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMiasma(void)
{
    // Render function stub
}
