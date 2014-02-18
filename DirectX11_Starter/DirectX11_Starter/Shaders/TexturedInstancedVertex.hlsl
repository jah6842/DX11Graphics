
// The constant buffer that holds our "per model" data
// - Each object you draw with this shader will probably have
//   slightly different data (at least for the world matrix)
cbuffer perModel : register( b0 )
{
	matrix world;
	matrix view;
	matrix projection;
};

// Defines what kind of data to expect as input
// - This should match our input layout!
struct VertexShaderInput
{
	float3 position		: POSITION;
	float2 TexCoord		: TEXCOORD;
	matrix instancePosition : INSTANCEPOS;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

// Defines the output data of our vertex shader
// - At a minimum, you'll need an SV_POSITION
// - Should match the pixel shader's input
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

// The entry point for our vertex shader
VS_OUTPUT main( VertexShaderInput input )
{
	// Set up output
	VS_OUTPUT output;

	// Calculate output position
	matrix viewProj = mul(view, projection);
	matrix final = mul(input.instancePosition, viewProj);
	output.Pos = mul(float4(input.position, 1.0f), final);

	// Texture UVs
	output.TexCoord = input.TexCoord;

	return output;
}