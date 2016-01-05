/*
*
* Copyright 2013-2016 Sebastien.warin.fr
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DvsSDKAPI.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace WinformDVRControl {

	/// <summary>
	/// Summary for WinformDVRControlControl
	/// </summary>
	public ref class WinformDVRControlControl : public System::Windows::Forms::UserControl
	{
	public:
		property String^ Host { 
		   public: String^ get() { return host; }
		   public: void set(String^ value) { host = value; }
		}
		property String^ Username { 
		   public: String^ get() { return username; }
		   public: void set(String^ value) { username = value; }
		}
		property String^ Password { 
		   public: String^ get() { return password; }
		   public: void set(String^ value) { password = value; }
		}
		property int Port {
		   public: int get() { return port; }
		   public: void set(int value) { port = value; }
		}
		property int Channel {
		   public: int get() { return channel; }
		   public: void set(int value) { channel = value; }
		}

		WinformDVRControlControl(void)
		{
			port = 40001;
			channel = 1;
			InitializeComponent();
			DVS_Init();
		}

		bool Connect()
		{
			if(!m_hDvs)
			{
				IntPtr hostPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(host);
				char* hostValue = static_cast<char*>(hostPtr.ToPointer());
				IntPtr userPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(username);
				char* userValue = static_cast<char*>(userPtr.ToPointer());
				IntPtr pwdPrt = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(password);
				char* pwdValue = static_cast<char*>(pwdPrt.ToPointer());

				HANDLE hDvs = NULL;
				DVS_SetConnectTime(4300,NULL);
				hDvs = DVS_Login(hostValue,port + 2,userValue,pwdValue);
				if(hDvs)
				{
					m_hDvs = hDvs;
					//AfxMessageBox(_T("Login successful"));
					return true;
				}
				else
				{
					CString szErrCode = _T("");
					szErrCode.Format(_T("Login failed, error code:%d"),DVS_GetLastError());
					AfxMessageBox(szErrCode);
					return false;
				}			
			}

			return true;
		}

		void PlayStream()
		{
			if(m_hDvs)
			{
				if(!m_hRealHandle)
				{
					HANDLE hRealHandle = NULL;
					BOOL bRet = DVS_OpenRealStream(m_hDvs,NULL,0,channel,(HWND)Handle.ToPointer(),hRealHandle);
					if(!bRet)
					{
						CString szErrTxt = _T("");
						szErrTxt.Format(_T("Open real stream failed with error code:%d"),DVS_GetLastError());
						AfxMessageBox(szErrTxt);
					}
					m_hRealHandle = hRealHandle;
				}
				DVS_PlayRealStream(m_hRealHandle,  NULL);
			}
			else
			{
				AfxMessageBox(_T("Please login!"));
			}
		}

		void SetAlarmIn(bool value)
		{
			if(m_hDvs)
			{
				DVS_SetAlarmIn(m_hDvs, channel, value);
			}
		}

		void SetAlarmOut(bool value)
		{
			if(m_hDvs)
			{
				DVS_SetAlarmOut(m_hDvs, channel, value);
			}
		}

		void Capture(String^ path)
		{
			if(m_hRealHandle)
			{
				IntPtr pchPicFileNamePrt = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path);
				char* pchPicFileName = static_cast<char*>(pchPicFileNamePrt.ToPointer());

				DVS_RealCapBmp(m_hRealHandle, pchPicFileName);
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WinformDVRControlControl()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnLoad(EventArgs^ e) override
		{
			
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		System::String^ host;
		int port;  
		System::String^ username;
		System::String^ password;
		int channel;

		HANDLE m_hRealHandle;
		static HANDLE m_hDvs;
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
