cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};

struct Vin
{
	float4 position : POSITION;
	float3 tex : TEXCOORD0;
};

struct Pin
{
	float4 position : SV_POSITION;
	float3 tex : TEXCOORD0;
};
Pin VShader(Vin input)
{
	Pin output;


	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.position.xyz;

	return output;
}
TextureCube shaderTextures;
SamplerState SampleType;
float4 PShader(Pin input) : SV_TARGET
{
	// Get the pixel color from the first texture.
	return shaderTextures.Sample(SampleType, input.tex);
}
