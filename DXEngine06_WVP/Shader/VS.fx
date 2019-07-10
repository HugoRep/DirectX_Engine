struct vs_input
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct vs_output
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

//¡§¡° ºŒ¿Ã¥ı.
//float4 main(float4 pos: POSITION):SV_POSITION{return pos;}
vs_output main(vs_input input)
{
	vs_output output;
	output.position = input.position;
	output.color = input.color;

	return output;
}