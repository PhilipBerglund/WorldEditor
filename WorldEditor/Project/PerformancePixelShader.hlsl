struct PS_INPUT
{
    float4 position : SV_POSITION;
};

cbuffer MODELTIME : register(b1)
{
    float modeltime;
}

cbuffer LIMIT : register(b2)
{
    float limit;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 OK = float4(0.0f, 1.0f, 0.0f, 1.0f);
    float4 NOT = float4(1.0f, 0.0f, 0.0f, 1.0f);
    float4 color = NOT;

    float rangeMin = 0.0f;
    float rangeMax = 1.0f;
    float oldRangeMin = limit * 0.2f;
    float oldRangeMax = limit;
    
    float oldRange = (oldRangeMax - oldRangeMin);
    float newRange = (rangeMax - rangeMin);
    float amount = 0.0f;
    
    //amount = (((modeltime - oldRangeMin) * newRange) / oldRange) + rangeMin;
    
    amount = (((modeltime - oldRangeMin) * (rangeMax - rangeMin)) / (oldRangeMax - oldRangeMin)) + rangeMin;
    float4 amountCol = float4(amount, 0.0f, amount, 0.0f);
    
    //if (modeltime < limit)
    //{
    //    color = OK;
    //}
    

    color = lerp(OK, NOT, amountCol);
    
    return color;
}