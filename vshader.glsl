#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 mvp_matrix2;
uniform mat4 camera;
uniform mat4 mvp_projection;
attribute vec4 a_position;
attribute vec2 a_texcoord;


varying vec2 v_texcoord;

void main()
{
    // Calculate vertex position in screen space
    gl_Position =mvp_matrix2 * mvp_projection * camera * mvp_matrix * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
