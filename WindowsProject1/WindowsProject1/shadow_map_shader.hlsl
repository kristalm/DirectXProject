
cbuffer buff
{
	matrix world;
	matrix view;
	matrix proj;
	matrix light_view;
	matrix light_proj;
};


struct Vin
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct Pin
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 lightViewPosition : TEXCOORD1;
};

Pin VShader(Vin input)
{
	Pin output;

	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.lightViewPosition = mul(input.position, world);
	output.lightViewPosition = mul(output.lightViewPosition, light_view);
	output.lightViewPosition = mul(output.lightViewPosition, light_proj);

	output.tex = input.tex;

	output.normal = mul(input.normal, (float3x3)world);

	output.normal = normalize(output.normal);

	return output;
}

Texture2D shaderTexture : register(t0);
Texture2D depthMapTexture : register(t1);

SamplerState SampleTypeClamp : register(s0);
SamplerState SampleTypeWrap  : register(s1);

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

float4 PShader(Pin input) : SV_TARGET
{
	float bias;
float4 color;
float2 projectTexCoord;
float depthValue;
float lightDepthValue;
float lightIntensity;
float4 textureColor;
float3 lightDir;
lightDir = -lightDirection;

bias = 0.001f;

color = ambientColor;

projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

if ((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
{
	depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

	lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

	if (lightDepthValue < depthValue)
	{
			lightIntensity = saturate(dot(input.normal, lightDir));

		if (lightIntensity > 0.0f)
			color += (diffuseColor * lightIntensity);

			color = saturate(color);
		}
	}
}
	else
{lightIntensity = saturate(dot(input.normal, lightDir));
	if (lightIntensity > 0.0f)
	{
		color += (diffuseColor * lightIntensity);
		color = saturate(color);
	}
}


color = color * textureColor;

return color;
}