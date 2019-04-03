
#define NUM_LIGHTS 4

cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};
cbuffer LightPositionBuffer
{
	float4 lightPosition[NUM_LIGHTS];
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
	float3 lightPos1 : TEXCOORD1;
};

Pin VShader(Vin input)
{
	Pin output;
	float4 worldPosition;

	input.position.w = 1.0f;

	output.position = mul(input.position, world);

	output.tex = input.tex;

	output.normal = mul(input.normal, (float3x3)world);

	output.normal = normalize(output.normal);

	worldPosition = mul(input.position, world);
    output.lightPos1.xyz = lightPosition[0].xyz - worldPosition.xyz;

	output.lightPos1 = normalize(output.lightPos1);

	return output;
}
#define NUM_LIGHTS 4

Texture2D shaderTexture;
SamplerState SampleType;
cbuffer LightColorBuffer
{
	float4 diffuseColor[NUM_LIGHTS];
};

float4 PShader(Pin input) : SV_TARGET
{
	float4 textureColor;
float lightIntensity1, lightIntensity2, lightIntensity3, lightIntensity4;
float4 color, color1, color2, color3, color4;
lightIntensity1 = saturate(dot(input.normal, input.lightPos1));

color1 = diffuseColor[0] * lightIntensity1;

textureColor = shaderTexture.Sample(SampleType, input.tex);
color = saturate(color1) * textureColor;

return color;
}
