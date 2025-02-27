#include "kernel/ocl/common.cl"


__kernel void ssandPile_ocl (__global unsigned *in, __global unsigned *out)
{
  int x = get_global_id (0);
  int y = get_global_id (1);

  //TODO
}

#ifdef GL_BUFFER_SHARING

// DO NOT MODIFY: this kernel updates the OpenGL texture buffer
// This is a ssandPile-specific version (generic version is defined in common.cl)
__kernel void ssandPile_update_texture (__global unsigned *cur, __write_only image2d_t tex)
{
  int y = get_global_id (1);
  int x = get_global_id (0);
  int2 pos = (int2)(x, y);
  unsigned c = cur [y * DIM + x];
  unsigned r = 0, v = 0, b = 0;

  if (c == 1)
    v = 255;
  else if (c == 2)
    b = 255;
  else if (c == 3)
    r = 255;
  else if (c == 4)
    r = v = b = 255;
  else if (c > 4)
    r = v = b = (2 * c);

  c = rgb (r, v, b);
  write_imagef (tex, pos, color_to_float4 (c));
}

#endif
