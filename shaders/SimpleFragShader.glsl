#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D tex_0; uniform sampler2D tex_1; uniform sampler2D tex_2; uniform sampler2D tex_3; uniform sampler2D tex_4; uniform sampler2D tex_5; uniform sampler2D tex_6; uniform sampler2D tex_7;
uniform sampler2D tex_8; uniform sampler2D tex_9; uniform sampler2D tex_10; uniform sampler2D tex_11; uniform sampler2D tex_12; uniform sampler2D tex_13; uniform sampler2D tex_14; uniform sampler2D tex_15;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 texture;
	float tid;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);

		switch (tid)
		{
			case 0: texColor = texture(tex_0, fs_in.texture); break;
			case 1: texColor = texture(tex_1, fs_in.texture); break;
			case 2: texColor = texture(tex_2, fs_in.texture); break;
			case 3: texColor = texture(tex_3, fs_in.texture); break;
			case 4: texColor = texture(tex_4, fs_in.texture); break;
			case 5: texColor = texture(tex_5, fs_in.texture); break;
			case 6: texColor = texture(tex_6, fs_in.texture); break;
			case 7: texColor = texture(tex_7, fs_in.texture); break;
			case 8: texColor = texture(tex_8, fs_in.texture); break;
			case 9: texColor = texture(tex_9, fs_in.texture); break;
			case 10: texColor = texture(tex_10, fs_in.texture); break;
			case 11: texColor = texture(tex_11, fs_in.texture); break;
			case 12: texColor = texture(tex_12, fs_in.texture); break;
			case 13: texColor = texture(tex_13, fs_in.texture); break;
			case 14: texColor = texture(tex_14, fs_in.texture); break;
			case 15: texColor = texture(tex_15, fs_in.texture); break;
		} 
		
	}
	color = texColor;
}