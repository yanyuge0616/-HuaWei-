#ifndef _TOOLS_H_
#define _TOOLS_H_
#include<graphics.h>

void SetWindowNewStyle(int w,int h)
{
	// ȥ������
	SetWindowLong(GetHWnd(), GWL_STYLE, GetWindowLong(GetHWnd(), GWL_STYLE) & ~WS_CAPTION);
	// ��ʼ������ΪԲ��
	SetWindowRgn(GetHWnd(), CreateEllipticRgn(0, 0, w, h), true);
}
//png͸����ͼ
void drawImg(IMAGE* pimg, int x, int y)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();
	DWORD* src = GetImageBuffer(pimg);
	int dst_width = ::getwidth();			//���ڿ��
	int dst_height = ::getheight();
	int _w = pimg->getwidth();
	int _h = pimg->getheight();

	// ������ͼ��ʵ�ʳ���
	int iwidth = (x + _w > dst_width) ? dst_width - x : _w;		// �������ұ߽�
	int iheight = (y + _h > dst_height) ? dst_height - y : _h;	// �������±߽�
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }				// ��������߽�
	if (y < 0) { src += (_w * -y);	iheight -= -y;	y = 0; }				// �������ϱ߽�


	// ������ͼ��ʼλ��
	dst += (dst_width * y + x);

	// ʵ��͸����ͼ
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			byte a = (byte)(src[ix] >> 24);//����͸��ͨ����ֵ[0,256) 0Ϊ��ȫ͸�� 255Ϊ��ȫ��͸��
			if (a > 100)
			{
				dst[ix] = src[ix];
			}
		}
		//������һ��
		dst += dst_width;
		src += _w;
	}
}
//ȥ�����ڱ����Ժ��ܹ�����ƶ�����
void mouseEvent()
{
	//���������ڵ�ǰ�������Ͻǵ�����(�������봰�����ϵĵĿ�Ⱥ͸߶�)
	static POINT WndPtSize;
	static bool isMove = false;
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)	//�������
		{
			//��ȡ�����������Ļ���Ͻǵ� ���Ͻ����꣬�����½�����
			RECT wndRect;
			GetWindowRect(GetHWnd(), &wndRect);


			//��ȡ������������Ļ������
			POINT curPos;
			GetCursorPos(&curPos);

			//���������ڵ�ǰ�������Ͻǵ�����
			WndPtSize.x = curPos.x - wndRect.left;
			WndPtSize.y = curPos.y - wndRect.top;

			isMove = true;
		}
		else if (msg.uMsg == WM_LBUTTONUP)//�������
		{
			isMove = false;
		}
		else if (msg.uMsg == WM_MOUSEMOVE)//����ƶ�
		{
			if (isMove)
			{
				POINT CursorPos;
				GetCursorPos(&CursorPos);
				/*�Ѵ����ƶ�����Ļ��x��y��λ��
				* @hwnd:���ھ��
				* @hwndInsertAfter:���ڵ�z˳��  HWND_TOPMOST {��ǰ��, λ���κζ������ڵ�ǰ��}
				* @X��Y: �������Ͻǵ���λ�ã��������Ļ��
				* @cx��xy: ���ڴ�С
				* @uFlags:SWP_NOSIZE {���� cx��cy, ���ִ�С}
				*/
				SetWindowPos(GetHWnd(), HWND_TOPMOST, CursorPos.x - WndPtSize.x, CursorPos.y - WndPtSize.y, 0, 0, SWP_NOSIZE);
				//CursorPos.x - WndPtSize.x	//��ȡ��ǰ�������Ͻ��������Ļ������
				//CursorPos.y - WndPtSize.y

				//printf("%d %d\n", CursorPos.x - WndPtSize.x, CursorPos.y - WndPtSize.y);
			}
		}
		else if (msg.uMsg == WM_RBUTTONDOWN)//�Ҽ�����
		{
			exit(0);
		}
	}
}

#endif // !_TOOLS_H_

