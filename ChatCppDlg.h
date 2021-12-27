// ChatCppDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ChatCpp.h"
#include "Sock.h"
#include "vector"
#include "map"

typedef struct {
    TCHAR p;
    TCHAR q;
}key;

TCHAR prost[100] = {
    17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
    59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
    103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
    331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
    389, 397, 401, 409, 419, 421, 431, 433, 439, 443,
    449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541, 547, 557, 563, 569, 571, 577
};

std::map<CString, key>keys;

void GenerateKeys(const CString& s);
//Расширенный алгоритм Евклида
TCHAR gcdex(TCHAR a, TCHAR b, TCHAR& x, TCHAR& y);
TCHAR sqr(TCHAR x);
//Быстрое возведение в степень
TCHAR binpow(TCHAR a, TCHAR e, TCHAR mod);
CString Encrypt(const CString& s, const CString& port);
//Обратное по модулю
TCHAR invmod(TCHAR a, TCHAR m);
CString Decrypt(const CString& s, const CString& port);


const CString g_EmptyName = "Ваше имя?";
const CString g_strStopChat = "Остановить чат";
const CString g_strExitFromChat = "Выход из чата";


struct SENDBUFFER
{
	SENDBUFFER() 
	{
		typemessage = 0; 
		countpeople = 0;
		stopchat = false;
		encrypt = true;
		ZeroMemory(name, sizeof(TCHAR)*14); 
		ZeroMemory(buffer, sizeof(TCHAR)*202);
	}

	int typemessage;
	int countpeople;
	bool stopchat;
	bool encrypt;
	TCHAR name[14];
	TCHAR buffer[202];
};



// CChatCppDlg dialog
class CChatCppDlg : public CDialog
{
// Construction
public:
	CChatCppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHATCPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedRadioServer();
	afx_msg void OnBnClickedRadioClient();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonStopchat();
	afx_msg void OnClose();
	
	inline CString IntToStr(int number)
	{
		CString str;
		str.Format("%d", number);
		return str;
	}

	void OnAccept(void);
	void OnConnect(BOOL Error);
	void OnReceive(void);

private:

	// запрещает доступ к управлениям
	void DisabledControl(bool server);

	// разрешить доступ к управлениям после закрытия сокетов
	void EnabledControl(void);

	void StopChat(void);

	// Послать сообщение в чат.
	void SendToChat(CString strMessage);

	void SendBuffer(SENDBUFFER sb, bool toserver);

	void SendDisconnect(void);

	// Сервер отправляет клиентам количество людей в чате.
	void SendCountPeople(void);

	
	CButton m_ButtonSend;
	CButton m_ButtonStartServer;
	CButton m_ButtonStartClient;
	CButton m_ButtonStopChat;
	CEdit m_wndChat;
	CEdit m_wndName;
	CEdit m_wndIPAddress;
	CEdit m_wndPort;
	CEdit m_wndSend;
	CStatic m_wndCountPeople;

	CSock m_mainSocket;
	std::vector<CSock*> m_vecSockets;

	enum m_TypeMessage {tmCountPeople=1, tmChat, tmDisconnect};

	// Запрос имени чатующего.
	bool QueryName(void);
};
