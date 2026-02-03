#include "ffcc/pppParHitSphMat.h"

/*
 * --INFO--
 * PAL Address: 0x8014139c
 * PAL Size: 436b
 */
void pppParHitSphMat(void)
{
    extern int lbl_8032ED70;
    extern void* lbl_80431DC0[];
    extern float lbl_8032ED50[];
    extern int lbl_80431E00;
    extern float sqrtf(float);
    
    if (lbl_8032ED70 == 0) return;
    
    void* particle_data = lbl_80431DC0[0];
    if (particle_data == 0) return;
    
    // Simple particle loop
    for (int i = 0; i < lbl_80431E00; i++) {
        void* current_particle = (void*)((unsigned char*)particle_data + i * 0x40);
        if (current_particle == 0) continue;
        
        // Basic sphere collision check
        void* sphere_data = (void*)((unsigned char*)current_particle + 0x20);
        if (sphere_data == 0) continue;
        
        float* sphere_pos = (float*)sphere_data;
        float radius = sphere_pos[3];
        float radius_sq = radius * radius;
        
        // Simple distance check
        float dx = 0.0f;  // TODO: Get from particle position
        float dy = 0.0f;
        float dz = 0.0f;
        float dist_sq = dx * dx + dy * dy + dz * dz;
        
        if (dist_sq <= radius_sq) {
            // Set collision flag
            unsigned int* flags = (unsigned int*)((unsigned char*)current_particle + 0x8);
            *flags |= 0x1;
            
            if (dist_sq > 0.001f) {
                float dist = sqrtf(dist_sq);
                float inv_dist = 1.0f / dist;
                float nx = dx * inv_dist;
                float ny = dy * inv_dist; 
                float nz = dz * inv_dist;
                
                // Apply material matrix transform
                float* matrix = &lbl_8032ED50[32];
                float result_x = nx * matrix[0] + ny * matrix[4] + nz * matrix[8];
                float result_y = nx * matrix[1] + ny * matrix[5] + nz * matrix[9];
                float result_z = nx * matrix[2] + ny * matrix[6] + nz * matrix[10];
                
                // Update velocity
                float* velocity = (float*)((unsigned char*)current_particle + 0x30);
                float bounce = matrix[15];
                velocity[0] = result_x * bounce;
                velocity[1] = result_y * bounce;
                velocity[2] = result_z * bounce;
                
                // Update color
                unsigned char* color = (unsigned char*)((unsigned char*)current_particle + 0x3C);
                color[0] = (unsigned char)(matrix[12] * 255.0f);
                color[1] = (unsigned char)(matrix[13] * 255.0f);
                color[2] = (unsigned char)(matrix[14] * 255.0f);
                color[3] = 255;
            }
        }
    }
}