#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

DWORD WINAPI sh1(LPVOID LpParam) {
    HDC hdc = GetDC(0), mem = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	LPRGBQUAD rgb = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP temp = CreateDIBSection(hdc, &bmi, 0, (void**)&rgb, 0, 0);
	SelectObject(mem, temp);
	for (;;) {
        hdc = GetDC(0);
        BitBlt(mem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		    for (int i = 0; i < w * h; i++) {
                int x = i % w, y = i / w;
                int exp = x * y;
                rgb[i].rgbRed += (exp >> 16) & 255;
                rgb[i].rgbGreen += (exp >> 8) & 255;
                rgb[i].rgbBlue += exp;
		}
		BitBlt(hdc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}
}

DWORD WINAPI sh2(LPVOID LpParam) {
    HDC hdc = GetDC(0), mem = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	LPRGBQUAD rgb = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP temp = CreateDIBSection(hdc, &bmi, 0, (void**)&rgb, 0, 0);
	SelectObject(mem, temp);
	for (;;) {
        hdc = GetDC(0);
		BitBlt(mem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			int x = i % w, y = i / w;
			rgb[i].rgbRed += 8;
			rgb[i].rgbGreen += 16;
			rgb[i].rgbBlue += 32;
		}
		BitBlt(hdc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}
}

DWORD WINAPI bounce(LPVOID LpParam) {
    HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int vx = 4, vy = 4, x = rand() % w, y = rand() % h;
	for (int i = 0;; i++) {
        hdc = GetDC(0);
		x += vx;
		y += vy;
		if (x > w) {
            x = w;
            vx *= -1;
		}
		else if (x < 0) {
            x = 0;
            vx *= -1;
		}

		if (y > h) {
            y = h;
            vy *= -1;
		}
		else if (y < 0) {
            y = 0;
            vy *= -1;
		}
		HBRUSH brs = CreateSolidBrush(RGB(i & 255, (i >> 8) & 255, (i >> 16) & 255));
		SelectObject(hdc, brs);
		Ellipse(hdc, x, y, x + 32, y + 32);
		DeleteObject(brs)

		ReleaseDC(NULL, hdc); DeleteDC(hdc);
		Sleep(10);
	}
}

DWORD WINAPI rand1(LPVOID LpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	for (;;) {
        hdc = GetDC(0);
        BitBlt(hdc, rand() % 256, rand() % 256, w, h, hdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}
}

DWORD WINAPI texts(LPVOID LpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	for (;;) {
        hdc = GetDC(0);
        SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
        HBRUSH brs = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, brs);TextOutA(hdc, rand() % w, rand() % h, "window.exe", 10);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}
}

void WINAPI so1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 7] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(t*(42&t>>10));
    }
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI so2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 7] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(6*t&t>>8|t>>4|t>>7);
    }
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI so3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 10] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(t-(t^t>>8));
    }
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI so4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 7] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(t-(t^t>>8));
    }
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI so5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 7] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(t*(t-(t^t>>8)));
    }
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
    srand(time(NULL));
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);
    int res = MessageBox(NULL, "This executable contains a few GDI payloads.\nContinue?", "Notice | window.exe by fly_ee", MB_ICONWARNING | MB_YESNO);
    if (res == IDNO) return 0;
    res = MessageBox(NULL, "if you don't want to end up in the hospital, Click on 'No'\n(im not responsible for ur hospital bills lil bro)\nStill continue?", "Epilepsy warning", MB_ICONWARNING | MB_YESNO);
    if (res == IDNO) return 0;

    Sleep(1000);
    InvalidateRect(0, 0, 0);
    so1();
    HANDLE thr1 = CreateThread(0, 0, sh1, 0, 0, 0);
    Sleep(7000);
    TerminateThread(thr1, 0);
    CloseHandle(thr1);
    Sleep(1000);
    InvalidateRect(0, 0, 0);
    so2();
    HANDLE thr2 = CreateThread(0, 0, sh2, 0, 0, 0);
    Sleep(7000);
    TerminateThread(thr2, 0);
    CloseHandle(thr2);
    Sleep(1000);
    InvalidateRect(0, 0, 0);
    so3();
    HANDLE thr3 = CreateThread(0, 0, bounce, 0, 0, 0);
    Sleep(10000);
    TerminateThread(thr3, 0);
    CloseHandle(thr3);
    Sleep(1000);
    InvalidateRect(0, 0, 0);
    so4();
    HANDLE thr4 = CreateThread(0, 0, rand1, 0, 0, 0);
    Sleep(7000);
    TerminateThread(thr4, 0);
    CloseHandle(thr4);
    Sleep(1000);
    InvalidateRect(0, 0, 0);
    so5();
    HANDLE thr5 = CreateThread(0, 0, texts, 0, 0, 0);
    Sleep(7000);
    TerminateThread(thr5, 0);
    CloseHandle(thr5);

    MessageBoxA(NULL, "alright, this is it", "The End", MB_ICONINFORMATION | MB_OK);
    return 0;
} // note: this isn't the original source code (i did some editing)
