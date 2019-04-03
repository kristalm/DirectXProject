
cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};
struct Vin
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct Pin
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};
Pin VShader(Vin input)
{
	Pin output;


	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	return output;
}

Texture2D shaderTexture;
SamplerState SampleType;

float4 PShader(Pin input) : SV_TARGET
{
	float4 textureColor;

textureColor = shaderTexture.Sample(SampleType, input.tex);

return textureColor;
}
