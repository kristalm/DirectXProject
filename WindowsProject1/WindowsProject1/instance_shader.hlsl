Texture2D shaderTexture;
SamplerState SampleType;
cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};
cbuffer LightBuffer
{
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};
float4 PShader(float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL) : SV_TARGET
{
	float4 textureColor;
float3 lightDir;
float lightIntensity;
float4 color;

textureColor = shaderTexture.Sample(SampleType, tex);

lightDir = -lightDirection;
lightIntensity = saturate(dot(normal, lightDir));

color = saturate(diffuseColor * lightIntensity);
color.a = 0.5f;
color = color * textureColor;


return color;
}
struct VOut
{
	float4 position :SV_POSITION;
	float2 textureC : TEXCOORD;
	float3 normal : NORMAL;
};

VOut VShader(float3 pos: POSITION, float2 text : TEXCOORD, float3 norm : NORMAL, float3 instance_pos : TEXCOORD1)
{
	VOut output;

	pos.x += instance_pos.x;
	pos.y += instance_pos.y;
	pos.z += instance_pos.z;

	output.position = mul(float4(pos, 1), world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.textureC = text;

	output.normal = mul(norm, (float3x3)world);


	output.normal = normalize(output.normal);

	return output;
}