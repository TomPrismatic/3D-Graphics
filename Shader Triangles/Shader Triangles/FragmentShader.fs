#version 450 core

in vec3 fragColor; 
in vec2 fragTexCoord;

out vec4 color; 

uniform float currentTime;
uniform sampler2D tex;

void main()
{ 
if (color.xyz == 1.0)
	{
		color = texture(tex, fragTexCoord);
		//color = vec4(0.0, 1.0, 0.0, 1.0);
	}

	else
	{
		vec3 colorTemp = fragColor * abs(sin(currentTime)); 
		color = vec4(colorTemp, 1.0); 
	}
}