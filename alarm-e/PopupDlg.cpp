#include "PopupDlg.h"

CPopupDlg::CPopupDlg(CString msg) : CDialogEx(CPopupDlg::IDD, NULL){
	m_strMsg = msg + "는 비속어 입니다. 사용을 자제해 주세요\n";

}
BOOL CPopupDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	if (::GetForegroundWindow() != this->m_hWnd){
		HWND h_active_wnd = ::GetForegroundWindow();
		if (h_active_wnd != NULL){
			DWORD thread_id = GetWindowThreadProcessId(h_active_wnd, NULL);
			DWORD current_thread_id = GetCurrentThreadId();
			if (current_thread_id != thread_id){
				if (AttachThreadInput(current_thread_id, thread_id, TRUE)){
					BringWindowToTop();
					AttachThreadInput(current_thread_id, thread_id, FALSE);
				}
			}
		}
	}
}