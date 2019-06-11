#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;

void main()
{
    // Set fragment color from texture
    if(v_texcoord == vec2(0.0f,0.0f))gl_FragColor = vec4(0.0f,0.7f,0.3f,1.0f);
    else
   gl_FragColor = texture2D(texture, v_texcoord); // for texture

   //gl_FragColor = vec4(0.0f,0.7f,0.3f,1.0f); //for color

}
