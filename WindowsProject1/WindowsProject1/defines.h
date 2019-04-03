#pragma once
#include <DirectXMath.h>

namespace GraphicsProj
{
	class defines
	{
	public:
		struct light_struct
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT2 text;
			DirectX::XMFLOAT3 norm;
		};
		defines();
		~defines();
	};
}
