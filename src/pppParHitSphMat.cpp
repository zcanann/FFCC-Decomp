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
    
    // Particle collision detection loop
    for (int i = 0; i < lbl_80431E00; i++) {
        void* current_particle = (void*)((unsigned char*)particle_data + i * 0x40);
        if (current_particle == 0) continue;
        
        // Get particle position
        float* particle_pos = (float*)((unsigned char*)current_particle + 0x10);
        float px = particle_pos[0];
        float py = particle_pos[1]; 
        float pz = particle_pos[2];
        
        // Get sphere collision data
        void* sphere_data = (void*)((unsigned char*)current_particle + 0x20);
        if (sphere_data == 0) continue;
        
        float* sphere_pos = (float*)sphere_data;
        float sx = sphere_pos[0];
        float sy = sphere_pos[1];
        float sz = sphere_pos[2];
        float radius = sphere_pos[3];
        
        // Calculate distance squared
        float dx = px - sx;
        float dy = py - sy;
        float dz = pz - sz;
        float dist_sq = dx * dx + dy * dy + dz * dz;
        float radius_sq = radius * radius;
        
        // Check collision
        if (dist_sq <= radius_sq) {
            // Collision detected, update particle state
            unsigned int* flags = (unsigned int*)((unsigned char*)current_particle + 0x8);
            *flags |= 0x1; // Set collision flag
            
            // Calculate collision normal (avoid division by zero)
            if (dist_sq > 0.001f) {
                float inv_dist = 1.0f / sqrtf(dist_sq);
                float nx = dx * inv_dist;
                float ny = dy * inv_dist;
                float nz = dz * inv_dist;
                
                // Apply matrix transformation for material response
                float* matrix_data = &lbl_8032ED50[32];
                float result_x = nx * matrix_data[0] + ny * matrix_data[4] + nz * matrix_data[8];
                float result_y = nx * matrix_data[1] + ny * matrix_data[5] + nz * matrix_data[9];
                float result_z = nx * matrix_data[2] + ny * matrix_data[6] + nz * matrix_data[10];
                
                // Update particle velocity based on material properties
                float* velocity = (float*)((unsigned char*)current_particle + 0x30);
                float bounce_factor = matrix_data[15];
                velocity[0] = result_x * bounce_factor;
                velocity[1] = result_y * bounce_factor;
                velocity[2] = result_z * bounce_factor;
            }
            
            // Update particle color based on material
            unsigned char* color = (unsigned char*)((unsigned char*)current_particle + 0x3C);
            float* matrix_data = &lbl_8032ED50[32];
            color[0] = (unsigned char)(matrix_data[12] * 255.0f);
            color[1] = (unsigned char)(matrix_data[13] * 255.0f);
            color[2] = (unsigned char)(matrix_data[14] * 255.0f);
            color[3] = 255;
        }
    }
}