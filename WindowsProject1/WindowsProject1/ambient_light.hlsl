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
	float4 ambientColor;
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

	color = ambientColor;

	lightDir = -lightDirection;
	lightIntensity = saturate(dot(normal, lightDir));

	if (lightIntensity > 0.0f)
	{
		color += (diffuseColor * lightIntensity);
	}
	color = saturate(color);

	color = color * textureColor;

	return color;
}
struct VOut
{
	float4 position :SV_POSITION;
	float2 textureC : TEXCOORD;
	float3 normal : NORMAL;
};

VOut VShader(float3 pos: POSITION, float2 text : TEXCOORD, float3 norm : NORMAL)
{
	VOut output;

	output.position = mul(float4(pos, 1), world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.textureC = text;

	output.normal = mul(norm, (float3x3)world);


	output.normal = normalize(output.normal);

	return output;
}