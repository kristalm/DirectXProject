cbuffer buff
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

	output.tex = input.tex;

	return output;
}
Texture2D shaderTextures[2];
SamplerState SampleType;
float4 PShader(Pin input) : SV_TARGET
{
	float4 color1;
	float4 color2;
	float4 blendColor;
	
	color1 = shaderTextures[0].Sample(SampleType, input.tex);
	
	color2 = shaderTextures[1].Sample(SampleType, input.tex);
	
	blendColor = color1 * color2 * 2.0;
	
	// Saturate the final color.
	blendColor = saturate(blendColor);
	
	return blendColor;
}
