precision mediump float;

varying vec2 texCoord;

uniform sampler2D tex;

void main()
{
    vec4 color = texture2D(tex, texCoord);
    gl_FragColor = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
}