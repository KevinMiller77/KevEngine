#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D textures[32];

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
		if (fs_in.tid < 2.0)
		{
			texColor = fs_in.color * texture(textures[0], fs_in.texture);
		} else if (fs_in.tid < 3.0)
		{
			texColor = fs_in.color * texture(textures[1], fs_in.texture);
		}else if (fs_in.tid < 4.0)
		{
			texColor = fs_in.color * texture(textures[2], fs_in.texture);
		}else if (fs_in.tid < 5.0)
		{
			texColor = fs_in.color * texture(textures[3], fs_in.texture);
		}else if (fs_in.tid < 6.0)
		{
			texColor = fs_in.color * texture(textures[4], fs_in.texture);
		}else if (fs_in.tid < 7.0)
		{
			texColor = fs_in.color * texture(textures[5], fs_in.texture);
		}else if (fs_in.tid < 8.0)
		{
			texColor = fs_in.color * texture(textures[6], fs_in.texture);
		}else if (fs_in.tid < 9.0)
		{
			texColor = fs_in.color * texture(textures[7], fs_in.texture);
		}else if (fs_in.tid < 10.0)
		{
			texColor = fs_in.color * texture(textures[8], fs_in.texture);
		}else if (fs_in.tid < 11.0)
		{
			texColor = fs_in.color * texture(textures[9], fs_in.texture);
		}else if (fs_in.tid < 12.0)
		{
			texColor = fs_in.color * texture(textures[10], fs_in.texture);
		}else if (fs_in.tid < 13.0)
		{
			texColor = fs_in.color * texture(textures[11], fs_in.texture);
		}else if (fs_in.tid < 14.0)
		{
			texColor = fs_in.color * texture(textures[12], fs_in.texture);
		}else if (fs_in.tid < 15.0)
		{
			texColor = fs_in.color * texture(textures[13], fs_in.texture);
		}else if (fs_in.tid < 16.0)
		{
			texColor = fs_in.color * texture(textures[14], fs_in.texture);
		}else
		{
			texColor = fs_in.color * texture(textures[15], fs_in.texture);
		}
		
	}
	color = texColor;
}