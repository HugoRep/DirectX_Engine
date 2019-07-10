struct ps_input
{
	float4 position :SV_POSITION;
	float4 color:COLOR;
};

//«»ºø ºŒ¿Ã¥ı.
float4 main(ps_input input) :SV_TARGET
{
	return input.color;
}