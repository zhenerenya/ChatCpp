// ChatCppDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ChatCpp.h"
#include "Sock.h"
#include "vector"
#include "map"

typedef struct {
	uint64_t p;
	uint64_t q;
}key;


static uint64_t prost[40] = {
	5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
	41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
	83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
	137, 139, 149, 151, 157, 163, 167, 173, 179, 181
};


static std::map<CString, key>keys;

void GenerateKeys(const CString& s);
//����������� �������� �������
uint64_t gcdex(uint64_t a, uint64_t b, uint64_t& x, uint64_t& y);
uint64_t sqr(uint64_t x);
//������� ���������� � �������
uint64_t binpow(uint64_t a, uint64_t e, uint64_t mod);
CString Encrypt(const CString& s, const CString& port);
//�������� �� ������
uint64_t invmod(uint64_t a, uint64_t m);
CString Decrypt(const CString& s, const CString& port);


const CString g_EmptyName = "���� ���?";
const CString g_strStopChat = "���������� ���";
const CString g_strExitFromChat = "����� �� ����";


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

	// ��������� ������ � �����������
	void DisabledControl(bool server);

	// ��������� ������ � ����������� ����� �������� �������
	void EnabledControl(void);

	void StopChat(void);

	// ������� ��������� � ���.
	void SendToChat(CString strMessage);

	void SendBuffer(SENDBUFFER sb, bool toserver);

	void SendDisconnect(void);

	// ������ ���������� �������� ���������� ����� � ����.
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

	// ������ ����� ���������.
	bool QueryName(void);
};
