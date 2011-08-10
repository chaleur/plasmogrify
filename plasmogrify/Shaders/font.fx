struct VSOut
{
    float4 Col : COLOR;    // vertex color
    float4 Pos : SV_POSITION;    // vertex screen coordinates
};

VSOut VS(float4 Col : COLOR, float4 Pos : POSITION)
{
    VSOut Output;
    Output.Pos = Pos; 
    Output.Col = Col;

    return Output;
}

float4 PS( float4 Col : COLOR ) : SV_Target
{
    return Col;
}
