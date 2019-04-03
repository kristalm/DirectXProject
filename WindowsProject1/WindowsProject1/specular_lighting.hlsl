cbuffer CBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};
cbuffer camera_buffer
{
	float3 camera_pos;
	float padding;
};
struct Pin
{
	float4 pos : SV_POSITION;
	float2 text : TEXCOORD0;
	float3 norm : NORMAL;
	float3 dir : TEXCOORD1;
};
Pin VShader(float4 position : POSITION, float2 textcoord : TEXCOORD0, float3 normal : NORMAL)
{
	Pin output;
	float4 world_pos;

	position.w = 1.0f;

	output.pos = mul(position, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, proj);

	output.text = textcoord;

	output.norm = mul(normal, (float3x3)world);

	output.norm = normalize(output.norm);

	world_pos = mul(position, world);

	output.dir = camera_pos.xyz - world_pos.xyz;

	output.dir = normalize(output.dir);

	return output;
}


Texture2D shaderTexture;
SamplerState SampleType;
cbuffer LightBuffer
{
	float4 ambient;
	float4 diffuse;
	float3 light_dir; //lightDirection
	float intensity; //specularpower
	float4 color;
};

float4 PShader(Pin input) : SV_TARGET
{
	float4 text_color_;
	float3 light_dir_;
	float lightIntensity;
	float4 color_;
	float3 reflect_;
	float4 specular_;


	text_color_ = shaderTexture.Sample(SampleType, input.text);

	color_ = ambient;

	specular_ = color;

	light_dir_ = -light_dir;

	lightIntensity = saturate(dot(input.norm, light_dir_));

	if (lightIntensity > 0.0f)
	{
		color_ += (diffuse * lightIntensity);

		color_ = saturate(color_);
		reflect_ = normalize(2 * lightIntensity * input.norm - light_dir_);
		specular_ = pow(saturate(dot(reflect_, input.dir)), intensity);
	}

	color_ = color_ * text_color_;
	color_ = saturate(color_ + specular_);

	return color_;
}
