#version 450 core

in vec3 fragColor; 
in vec2 fragTexCoord;

out vec4 color; 

uniform float currentTime;
uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{ 
	if (fragColor.r == 1.0f && fragColor.g == 1.0f && fragColor.b == 1.0f)
	{
		color = mix(texture(tex, fragTexCoord), texture(tex2, fragTexCoord), abs(sin(currentTime)));
		//color = vec4(0.0, 1.0, 0.0, 1.0);
		
	}

	else
	{
		vec3 colorTemp = fragColor * abs(sin(currentTime)); 
		color = vec4(colorTemp, 1.0); 
	}
}