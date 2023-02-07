#include "common.hlsl"

struct PARTICLE_PARAM
{
    bool IsActive;
    float Lifetime;
    float2 Size;
    float3 Position;
    float3 Velocity;
    float3 Gravity;
    float4 Color;
};

struct PARTICLE_DEFAULT_PARAM
{
    float Lifetime;
    float2 StartSizeMax;
    float2 StartSizeMin;
    float3 StartPosition;
    float3 StartVelocityMax;
    float3 StartVelocityMin;
    float3 Gravity;
    float4 Color;
};

RWStructuredBuffer<PARTICLE_PARAM> ParticleParam : register(u0);
AppendStructuredBuffer<uint> DeadList : register(u1);
ConsumeStructuredBuffer<uint> ParticlePool : register(u2);
RWStructuredBuffer<uint> ParticleCount : register(u3);

StructuredBuffer<PARTICLE_DEFAULT_PARAM> ParticleDefaultParam : register(t0);
StructuredBuffer<float> DeltaTime : register(t1);

float rand(float2 seed)
{
    return frac(sin(dot(seed.xy, float2(12.9898, 78.233))) * 43758.5453);
}

float2 rand2(float2 seed)
{
    return 2.0 * (float2(rand(seed * 1), rand(seed * 2)) - 0.5);
}

float3 rand3(float2 seed)
{
    return 2.0 * (float3(rand(seed * 1), rand(seed * 2), rand(seed * 3)) - 0.5);
}

[numthreads(1, 1, 1)]
void SetList()
{
    //uint c = ParticleCount[0];
    uint c = 10;
    for (uint i = 0; i < c; i++)
    {
        DeadList.Append(i);
    }
}

[numthreads(1, 1, 1)]
void Init(uint3 id : SV_DispatchThreadID)
{
    ParticleParam[id.x].IsActive = true;
    ParticleParam[id.x].Size = 1;
    ParticleParam[id.x].Lifetime = 1;
    
    //DeadList.Append(id.x);
}

[numthreads(1, 1, 1)]
void Emit()
{
    uint id = ParticlePool.Consume();
    
    float2 seed = float2(id + 1, id + 2);
    float2 size = ParticleDefaultParam[0].StartSizeMin;
    size += (ParticleDefaultParam[0].StartSizeMax - ParticleDefaultParam[0].StartSizeMin) * rand2(seed);
    float3 vel = ParticleDefaultParam[0].StartVelocityMin;
    vel += (ParticleDefaultParam[0].StartVelocityMax - ParticleDefaultParam[0].StartVelocityMin) * rand3(seed);
    float3 rot = rand3(seed + 3);
    
    PARTICLE_PARAM p;
    p.IsActive = true;
    //p.Lifetime = ParticleDefaultParam[0].Lifetime;
    p.Lifetime = 5;
    p.Size = 1;
    p.Position = ParticleDefaultParam[0].StartPosition;
    p.Velocity = vel;
    p.Gravity = ParticleDefaultParam[0].Gravity;
    p.Color = ParticleDefaultParam[0].Color;
    ParticleParam[id] = p;
}

[numthreads(1, 1, 1)]
void Update(uint3 id : SV_DispatchThreadID)
{
    PARTICLE_PARAM p = ParticleParam[id.x];
  
    if (p.IsActive)
    {
        //p.Lifetime -= DeltaTime[0];
        p.Lifetime -= 0.0167;
        //p.Position += p.Velocity;
        p.Position.y += 0.001;
        ////p.Velocity += p.Gravity * DeltaTime;
        //p.Velocity += p.Gravity;
      
        if (p.Lifetime <= 0.0)
        {
            p.IsActive = false;
            p.Size = 1;
    
            DeadList.Append(id.x);
        }
        ParticleParam[id.x] = p;
    }
}



















//// CSÝ’è
//struct CSInput
//{
//    uint3 groupThread : SV_GroupThreadID;
//    uint3 group : SV_GroupID;
//    uint groupIndex : SV_GroupIndex;
//    uint3 dispatch : SV_DispatchThreadID;
//};

//[numthreads(8, 1, 1)]
//void Init(CSInput input)
//{

//}
