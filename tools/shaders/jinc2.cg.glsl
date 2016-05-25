// GLSL shader autogenerated by cg2glsl.py.
#if defined(VERTEX)

#if __VERSION__ >= 130
#define COMPAT_VARYING out
#define COMPAT_ATTRIBUTE in
#define COMPAT_TEXTURE texture
#else
#define COMPAT_VARYING varying
#define COMPAT_ATTRIBUTE attribute
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif
COMPAT_VARYING     vec2 _texCoord;
COMPAT_VARYING     vec4 _color1;
COMPAT_VARYING     vec4 _position1;
COMPAT_VARYING     float _frame_rotation;
struct input_dummy {
    vec2 _video_size;
    vec2 _texture_size;
    vec2 _output_dummy_size;
    float _frame_count;
    float _frame_direction;
    float _frame_rotation;
};
struct out_vertex {
    vec4 _position1;
    vec4 _color1;
    vec2 _texCoord;
};
out_vertex _ret_0;
vec4 _r0008;
COMPAT_ATTRIBUTE vec4 gl_Vertex;
COMPAT_ATTRIBUTE vec4 COLOR;
COMPAT_ATTRIBUTE vec4 gl_MultiTexCoord0;
COMPAT_VARYING vec4 COL0;
COMPAT_VARYING vec4 TEX0;
 
uniform int FrameDirection;
uniform int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;
void main()
{
    _r0008 = gl_Vertex.x*gl_ModelViewProjectionMatrix[0];
    _r0008 = _r0008 + gl_Vertex.y*gl_ModelViewProjectionMatrix[1];
    _r0008 = _r0008 + gl_Vertex.z*gl_ModelViewProjectionMatrix[2];
    _r0008 = _r0008 + gl_Vertex.w*gl_ModelViewProjectionMatrix[3];
    _ret_0._position1 = _r0008;
    _ret_0._color1 = COLOR;
    _ret_0._texCoord = gl_MultiTexCoord0.xy;
    gl_Position = _r0008;
    COL0 = COLOR;
    TEX0.xy = gl_MultiTexCoord0.xy;
    return;
    COL0 = _ret_0._color1;
    TEX0.xy = _ret_0._texCoord;
} 
#elif defined(FRAGMENT)

#if __VERSION__ >= 130
#define COMPAT_VARYING in
#define COMPAT_TEXTURE texture
out vec4 FragColor;
#else
#define COMPAT_VARYING varying
#define FragColor gl_FragColor
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif
COMPAT_VARYING     vec2 _texCoord;
COMPAT_VARYING     vec4 _color1;
COMPAT_VARYING     float _frame_rotation;
struct input_dummy {
    vec2 _video_size;
    vec2 _texture_size;
    vec2 _output_dummy_size;
    float _frame_count;
    float _frame_direction;
    float _frame_rotation;
};
struct out_vertex {
    vec4 _color1;
    vec2 _texCoord;
};
vec4 _ret_0;
vec3 _TMP45;
float _TMP37;
vec3 _TMP44;
vec3 _TMP43;
vec3 _TMP42;
vec3 _TMP41;
vec4 _TMP32;
vec4 _TMP31;
vec4 _TMP30;
vec4 _TMP29;
vec4 _TMP28;
vec4 _TMP27;
vec4 _TMP26;
vec4 _TMP25;
vec4 _TMP24;
vec4 _TMP23;
vec4 _TMP22;
vec4 _TMP21;
vec4 _TMP20;
vec4 _TMP19;
vec4 _TMP18;
vec4 _TMP17;
vec4 _TMP40;
vec4 _TMP39;
float _TMP50;
float _TMP49;
float _TMP48;
float _TMP47;
float _TMP38;
float _TMP46;
vec2 _TMP0;
uniform sampler2D Texture;
input_dummy _IN1;
vec2 _x0060;
float _TMP61;
vec2 _v0062;
vec2 _pt20062;
float _TMP69;
vec2 _v0070;
vec2 _pt20070;
float _TMP77;
vec2 _v0078;
vec2 _pt20078;
float _TMP85;
vec2 _v0086;
vec2 _pt20086;
vec4 _x0094;
vec4 _res0094;
vec4 _x0096;
vec4 _x0106;
float _TMP115;
vec2 _v0116;
vec2 _pt20116;
float _TMP123;
vec2 _v0124;
float _TMP131;
vec2 _v0132;
vec2 _pt20132;
float _TMP139;
vec2 _v0140;
vec2 _pt20140;
vec4 _x0148;
vec4 _res0148;
vec4 _x0150;
vec4 _x0160;
float _TMP169;
vec2 _v0170;
vec2 _pt20170;
float _TMP177;
vec2 _v0178;
vec2 _pt20178;
float _TMP185;
vec2 _v0186;
vec2 _pt20186;
float _TMP193;
vec2 _v0194;
vec2 _pt20194;
vec4 _x0202;
vec4 _res0202;
vec4 _x0204;
vec4 _x0214;
float _TMP223;
vec2 _v0224;
vec2 _pt20224;
float _TMP231;
vec2 _v0232;
vec2 _pt20232;
float _TMP239;
vec2 _v0240;
vec2 _pt20240;
float _TMP247;
vec2 _v0248;
vec2 _pt20248;
vec4 _x0256;
vec4 _res0256;
vec4 _x0258;
vec4 _x0268;
vec2 _c0278;
vec2 _c0280;
vec2 _c0282;
vec2 _c0284;
vec2 _c0286;
vec2 _c0290;
vec2 _c0292;
vec2 _c0294;
vec2 _c0296;
vec2 _c0298;
vec2 _c0300;
vec2 _c0302;
vec2 _c0304;
vec2 _c0306;
vec2 _c0308;
vec3 _TMP309;
vec3 _TMP317;
vec3 _r0326;
vec3 _r0328;
vec3 _r0330;
vec3 _r0332;
vec4 _r0334;
vec3 _TMP345;
COMPAT_VARYING vec4 TEX0;
 
uniform int FrameDirection;
uniform int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;
void main()
{
    vec3 _color;
    vec2 _dx;
    vec2 _dy;
    vec2 _pc;
    vec2 _tc;
    _pc = TEX0.xy*TextureSize;
    _x0060 = _pc - vec2( 5.00000000E-01, 5.00000000E-01);
    _TMP0 = floor(_x0060);
    _tc = _TMP0 + vec2( 5.00000000E-01, 5.00000000E-01);
    _pt20062 = (_tc - vec2( 1.00000000E+00, 0.00000000E+00)) - vec2( 0.00000000E+00, 1.00000000E+00);
    _v0062 = _pt20062 - _pc;
    _TMP38 = dot(_v0062, _v0062);
    _TMP46 = inversesqrt(_TMP38);
    _TMP61 = 1.00000000E+00/_TMP46;
    _pt20070 = _tc - vec2( 0.00000000E+00, 1.00000000E+00);
    _v0070 = _pt20070 - _pc;
    _TMP38 = dot(_v0070, _v0070);
    _TMP46 = inversesqrt(_TMP38);
    _TMP69 = 1.00000000E+00/_TMP46;
    _pt20078 = (_tc + vec2( 1.00000000E+00, 0.00000000E+00)) - vec2( 0.00000000E+00, 1.00000000E+00);
    _v0078 = _pt20078 - _pc;
    _TMP38 = dot(_v0078, _v0078);
    _TMP46 = inversesqrt(_TMP38);
    _TMP77 = 1.00000000E+00/_TMP46;
    _pt20086 = (_tc + vec2( 2.00000000E+00, 0.00000000E+00)) - vec2( 0.00000000E+00, 1.00000000E+00);
    _v0086 = _pt20086 - _pc;
    _TMP38 = dot(_v0086, _v0086);
    _TMP46 = inversesqrt(_TMP38);
    _TMP85 = 1.00000000E+00/_TMP46;
    _x0094 = vec4(_TMP61, _TMP69, _TMP77, _TMP85);
    _x0096 = _x0094*1.38230085E+00;
    _TMP47 = sin(_x0096.x);
    _TMP48 = sin(_x0096.y);
    _TMP49 = sin(_x0096.z);
    _TMP50 = sin(_x0096.w);
    _TMP39 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _x0106 = _x0094*2.57610607E+00;
    _TMP47 = sin(_x0106.x);
    _TMP48 = sin(_x0106.y);
    _TMP49 = sin(_x0106.z);
    _TMP50 = sin(_x0106.w);
    _TMP40 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _res0094 = vec4(_x0094.x == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0094*_x0094)).x, _x0094.y == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0094*_x0094)).y, _x0094.z == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0094*_x0094)).z, _x0094.w == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0094*_x0094)).w);
    _pt20116 = _tc - vec2( 1.00000000E+00, 0.00000000E+00);
    _v0116 = _pt20116 - _pc;
    _TMP38 = dot(_v0116, _v0116);
    _TMP46 = inversesqrt(_TMP38);
    _TMP115 = 1.00000000E+00/_TMP46;
    _v0124 = _tc - _pc;
    _TMP38 = dot(_v0124, _v0124);
    _TMP46 = inversesqrt(_TMP38);
    _TMP123 = 1.00000000E+00/_TMP46;
    _pt20132 = _tc + vec2( 1.00000000E+00, 0.00000000E+00);
    _v0132 = _pt20132 - _pc;
    _TMP38 = dot(_v0132, _v0132);
    _TMP46 = inversesqrt(_TMP38);
    _TMP131 = 1.00000000E+00/_TMP46;
    _pt20140 = _tc + vec2( 2.00000000E+00, 0.00000000E+00);
    _v0140 = _pt20140 - _pc;
    _TMP38 = dot(_v0140, _v0140);
    _TMP46 = inversesqrt(_TMP38);
    _TMP139 = 1.00000000E+00/_TMP46;
    _x0148 = vec4(_TMP115, _TMP123, _TMP131, _TMP139);
    _x0150 = _x0148*1.38230085E+00;
    _TMP47 = sin(_x0150.x);
    _TMP48 = sin(_x0150.y);
    _TMP49 = sin(_x0150.z);
    _TMP50 = sin(_x0150.w);
    _TMP39 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _x0160 = _x0148*2.57610607E+00;
    _TMP47 = sin(_x0160.x);
    _TMP48 = sin(_x0160.y);
    _TMP49 = sin(_x0160.z);
    _TMP50 = sin(_x0160.w);
    _TMP40 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _res0148 = vec4(_x0148.x == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0148*_x0148)).x, _x0148.y == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0148*_x0148)).y, _x0148.z == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0148*_x0148)).z, _x0148.w == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0148*_x0148)).w);
    _pt20170 = (_tc - vec2( 1.00000000E+00, 0.00000000E+00)) + vec2( 0.00000000E+00, 1.00000000E+00);
    _v0170 = _pt20170 - _pc;
    _TMP38 = dot(_v0170, _v0170);
    _TMP46 = inversesqrt(_TMP38);
    _TMP169 = 1.00000000E+00/_TMP46;
    _pt20178 = _tc + vec2( 0.00000000E+00, 1.00000000E+00);
    _v0178 = _pt20178 - _pc;
    _TMP38 = dot(_v0178, _v0178);
    _TMP46 = inversesqrt(_TMP38);
    _TMP177 = 1.00000000E+00/_TMP46;
    _pt20186 = _tc + vec2( 1.00000000E+00, 0.00000000E+00) + vec2( 0.00000000E+00, 1.00000000E+00);
    _v0186 = _pt20186 - _pc;
    _TMP38 = dot(_v0186, _v0186);
    _TMP46 = inversesqrt(_TMP38);
    _TMP185 = 1.00000000E+00/_TMP46;
    _pt20194 = _tc + vec2( 2.00000000E+00, 0.00000000E+00) + vec2( 0.00000000E+00, 1.00000000E+00);
    _v0194 = _pt20194 - _pc;
    _TMP38 = dot(_v0194, _v0194);
    _TMP46 = inversesqrt(_TMP38);
    _TMP193 = 1.00000000E+00/_TMP46;
    _x0202 = vec4(_TMP169, _TMP177, _TMP185, _TMP193);
    _x0204 = _x0202*1.38230085E+00;
    _TMP47 = sin(_x0204.x);
    _TMP48 = sin(_x0204.y);
    _TMP49 = sin(_x0204.z);
    _TMP50 = sin(_x0204.w);
    _TMP39 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _x0214 = _x0202*2.57610607E+00;
    _TMP47 = sin(_x0214.x);
    _TMP48 = sin(_x0214.y);
    _TMP49 = sin(_x0214.z);
    _TMP50 = sin(_x0214.w);
    _TMP40 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _res0202 = vec4(_x0202.x == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0202*_x0202)).x, _x0202.y == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0202*_x0202)).y, _x0202.z == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0202*_x0202)).z, _x0202.w == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0202*_x0202)).w);
    _pt20224 = (_tc - vec2( 1.00000000E+00, 0.00000000E+00)) + vec2( 0.00000000E+00, 2.00000000E+00);
    _v0224 = _pt20224 - _pc;
    _TMP38 = dot(_v0224, _v0224);
    _TMP46 = inversesqrt(_TMP38);
    _TMP223 = 1.00000000E+00/_TMP46;
    _pt20232 = _tc + vec2( 0.00000000E+00, 2.00000000E+00);
    _v0232 = _pt20232 - _pc;
    _TMP38 = dot(_v0232, _v0232);
    _TMP46 = inversesqrt(_TMP38);
    _TMP231 = 1.00000000E+00/_TMP46;
    _pt20240 = _tc + vec2( 1.00000000E+00, 0.00000000E+00) + vec2( 0.00000000E+00, 2.00000000E+00);
    _v0240 = _pt20240 - _pc;
    _TMP38 = dot(_v0240, _v0240);
    _TMP46 = inversesqrt(_TMP38);
    _TMP239 = 1.00000000E+00/_TMP46;
    _pt20248 = _tc + vec2( 2.00000000E+00, 0.00000000E+00) + vec2( 0.00000000E+00, 2.00000000E+00);
    _v0248 = _pt20248 - _pc;
    _TMP38 = dot(_v0248, _v0248);
    _TMP46 = inversesqrt(_TMP38);
    _TMP247 = 1.00000000E+00/_TMP46;
    _x0256 = vec4(_TMP223, _TMP231, _TMP239, _TMP247);
    _x0258 = _x0256*1.38230085E+00;
    _TMP47 = sin(_x0258.x);
    _TMP48 = sin(_x0258.y);
    _TMP49 = sin(_x0258.z);
    _TMP50 = sin(_x0258.w);
    _TMP39 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _x0268 = _x0256*2.57610607E+00;
    _TMP47 = sin(_x0268.x);
    _TMP48 = sin(_x0268.y);
    _TMP49 = sin(_x0268.z);
    _TMP50 = sin(_x0268.w);
    _TMP40 = vec4(_TMP47, _TMP48, _TMP49, _TMP50);
    _res0256 = vec4(_x0256.x == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0256*_x0256)).x, _x0256.y == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0256*_x0256)).y, _x0256.z == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0256*_x0256)).z, _x0256.w == 0.00000000E+00 ? 3.56095362E+00 : ((_TMP39*_TMP40)/(_x0256*_x0256)).w);
    _dx = vec2( 1.00000000E+00, 0.00000000E+00)/TextureSize;
    _dy = vec2( 0.00000000E+00, 1.00000000E+00)/TextureSize;
    _tc = _tc/TextureSize;
    _c0278 = (_tc - _dx) - _dy;
    _TMP17 = COMPAT_TEXTURE(Texture, _c0278);
    _c0280 = _tc - _dy;
    _TMP18 = COMPAT_TEXTURE(Texture, _c0280);
    _c0282 = (_tc + _dx) - _dy;
    _TMP19 = COMPAT_TEXTURE(Texture, _c0282);
    _c0284 = (_tc + 2.00000000E+00*_dx) - _dy;
    _TMP20 = COMPAT_TEXTURE(Texture, _c0284);
    _c0286 = _tc - _dx;
    _TMP21 = COMPAT_TEXTURE(Texture, _c0286);
    _TMP22 = COMPAT_TEXTURE(Texture, _tc);
    _c0290 = _tc + _dx;
    _TMP23 = COMPAT_TEXTURE(Texture, _c0290);
    _c0292 = _tc + 2.00000000E+00*_dx;
    _TMP24 = COMPAT_TEXTURE(Texture, _c0292);
    _c0294 = (_tc - _dx) + _dy;
    _TMP25 = COMPAT_TEXTURE(Texture, _c0294);
    _c0296 = _tc + _dy;
    _TMP26 = COMPAT_TEXTURE(Texture, _c0296);
    _c0298 = _tc + _dx + _dy;
    _TMP27 = COMPAT_TEXTURE(Texture, _c0298);
    _c0300 = _tc + 2.00000000E+00*_dx + _dy;
    _TMP28 = COMPAT_TEXTURE(Texture, _c0300);
    _c0302 = (_tc - _dx) + 2.00000000E+00*_dy;
    _TMP29 = COMPAT_TEXTURE(Texture, _c0302);
    _c0304 = _tc + 2.00000000E+00*_dy;
    _TMP30 = COMPAT_TEXTURE(Texture, _c0304);
    _c0306 = _tc + _dx + 2.00000000E+00*_dy;
    _TMP31 = COMPAT_TEXTURE(Texture, _c0306);
    _c0308 = _tc + 2.00000000E+00*_dx + 2.00000000E+00*_dy;
    _TMP32 = COMPAT_TEXTURE(Texture, _c0308);
    _TMP41 = min(_TMP26.xyz, _TMP27.xyz);
    _TMP42 = min(_TMP23.xyz, _TMP41);
    _TMP309 = min(_TMP22.xyz, _TMP42);
    _TMP43 = max(_TMP26.xyz, _TMP27.xyz);
    _TMP44 = max(_TMP23.xyz, _TMP43);
    _TMP317 = max(_TMP22.xyz, _TMP44);
    _r0326 = _res0094.x*_TMP17.xyz;
    _r0326 = _r0326 + _res0094.y*_TMP18.xyz;
    _r0326 = _r0326 + _res0094.z*_TMP19.xyz;
    _r0326 = _r0326 + _res0094.w*_TMP20.xyz;
    _r0328 = _res0148.x*_TMP21.xyz;
    _r0328 = _r0328 + _res0148.y*_TMP22.xyz;
    _r0328 = _r0328 + _res0148.z*_TMP23.xyz;
    _r0328 = _r0328 + _res0148.w*_TMP24.xyz;
    _color = _r0326 + _r0328;
    _r0330 = _res0202.x*_TMP25.xyz;
    _r0330 = _r0330 + _res0202.y*_TMP26.xyz;
    _r0330 = _r0330 + _res0202.z*_TMP27.xyz;
    _r0330 = _r0330 + _res0202.w*_TMP28.xyz;
    _color = _color + _r0330;
    _r0332 = _res0256.x*_TMP29.xyz;
    _r0332 = _r0332 + _res0256.y*_TMP30.xyz;
    _r0332 = _r0332 + _res0256.z*_TMP31.xyz;
    _r0332 = _r0332 + _res0256.w*_TMP32.xyz;
    _color = _color + _r0332;
    _r0334.x = dot(_res0094, vec4( 1.00000000E+00, 1.00000000E+00, 1.00000000E+00, 1.00000000E+00));
    _r0334.y = dot(_res0148, vec4( 1.00000000E+00, 1.00000000E+00, 1.00000000E+00, 1.00000000E+00));
    _r0334.z = dot(_res0202, vec4( 1.00000000E+00, 1.00000000E+00, 1.00000000E+00, 1.00000000E+00));
    _r0334.w = dot(_res0256, vec4( 1.00000000E+00, 1.00000000E+00, 1.00000000E+00, 1.00000000E+00));
    _TMP37 = dot(_r0334, vec4( 1.00000000E+00, 1.00000000E+00, 1.00000000E+00, 1.00000000E+00));
    _color = _color/_TMP37;
    _TMP45 = min(_TMP317, _color);
    _TMP345 = max(_TMP309, _TMP45);
    _color = _color + 5.00000000E-01*(_TMP345 - _color);
    _ret_0 = vec4(_color.x, _color.y, _color.z, 1.00000000E+00);
    FragColor = _ret_0;
    return;
} 
#endif
