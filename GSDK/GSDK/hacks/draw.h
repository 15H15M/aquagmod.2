
namespace H
{
	namespace Draw
	{
		class Vertexs
		{
		public:
			float	x = 0.f;
			float	y = 0.f;
			float	z = 0.f;
		};
		void DrawLine(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawLine(x1, y1, x2, y2);
			surface()->DrawSetColor(255, 255, 255, 255);
		}
		void DrawLine(Vector2D pos1, Vector2D pos2, Color color = Color(255, 255, 255, 255))
		{
			DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, color);
		}
		void DrawOutlineRect(int x, int y, int w, int h, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawOutlinedRect(x, y, x + w, y + h);
			surface()->DrawSetColor(255, 255, 255, 255);
		}
		void DrawCircle(int x, int y, int radius,int segments, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawOutlinedCircle(x, y, radius, segments);
			surface()->DrawSetColor(Color(255, 255, 255, 255));
		}
		void DrawRect(int x = 0, int y = 0, int w = 100, int h = 100, Color color = Color(255,255,255,255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawFilledRect(x, y, x + w, y + h);
			surface()->DrawSetColor(255, 255, 255, 255);
		}

		void Drawtext(const char* text = "Sample Text", int font = 1, int x = 0, int y = 0, Color color = Color(255,255/2,0,255))
		{
//#define mxsz 256
			//text = "text1337";
			size_t cSize = strlen(text);
			/*if (cSize >= mxsz)
			{
				text = "Error:TooManySymbols";
				cSize = sizeof("Error:TooManySymbols");
			}*/
			wchar_t wc[256] = L"";
			//mbstowcs(wc, text, cSize);
			OemToCharBuff(text, wc, cSize);
			surface()->DrawSetTextFont(font);
			surface()->DrawSetTextColor(color);
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wc, cSize);
			//surface()->DrawSetTextColor(255,255,255,255);
			//delete wc;
		}
	};
};