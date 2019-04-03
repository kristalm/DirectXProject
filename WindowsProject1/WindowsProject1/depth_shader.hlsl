/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};


//////////////
// TYPEDEFS //
//////////////
struct Vin
{
	float4 position : POSITION;
};
struct Pin
{
	float4 position : SV_POSITION;
	float4 depthPosition : TEXTURE0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
Pin VShader(Vin input)
{
	Pin output;


	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);
		// Store the position value in a second input value for depth value calculations.
		output.depthPosition = output.position;

	return output;
}

////////////////////////////////////////////////////////////////////////////////
// Filename: depth.ps
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PShader(Pin input) : SV_TARGET
{
	float depthValue;
float4 color;
// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
depthValue = input.depthPosition.z / input.depthPosition.w;

// First 10% of the depth buffer color red.
if (depthValue < 0.9f)
{
	color = float4(1.0, 0.0f, 0.0f, 1.0f);
}

// The next 0.025% portion of the depth buffer color green.
if (depthValue > 0.9f)
{
	color = float4(0.0, 1.0f, 0.0f, 1.0f);
}

// The remainder of the depth buffer color blue.
if (depthValue > 0.925f)
{
	color = float4(0.0, 0.0f, 1.0f, 1.0f);
}

return color;
}
