package com.twinsprite.demokit.androidNFC;

import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NfcAdapter;
import android.nfc.tech.NfcF;
import android.os.Bundle;
import android.nfc.tech.IsoDep;
import android.nfc.tech.MifareClassic;
import android.nfc.tech.MifareUltralight;
import android.nfc.tech.Ndef;
import android.nfc.tech.NfcA;
import android.nfc.tech.NfcB;
import android.nfc.tech.NfcV;

import com.unity3d.player.UnityPlayer;
import com.unity3d.player.UnityPlayerActivity;

public class ScanActivity extends UnityPlayerActivity
{
	// background scan mode
	private boolean backgroundScan = false;
	
	// Callback object and method
	private String gameObject;
	private String methodName;

	private NfcAdapter mAdapter = null;
	private PendingIntent mPendingIntent;
	private IntentFilter[] mFilters;
	private String[][] mTechLists;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Create NFC Adapter
		mAdapter = NfcAdapter.getDefaultAdapter(this);

		// Pending intent
		mPendingIntent = PendingIntent.getActivity(this, 0,
				new Intent(this, ScanActivity.class).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);

		// Setup an intent filter
		IntentFilter filter = new IntentFilter();
		filter.addAction(NfcAdapter.ACTION_TAG_DISCOVERED);
		filter.addAction(NfcAdapter.ACTION_NDEF_DISCOVERED);
		filter.addAction(NfcAdapter.ACTION_TECH_DISCOVERED);
		mFilters = new IntentFilter[] { filter };

		// Setup a tech list for all NfcF tags
		mTechLists = new String[][] {
			new String[] {
					NfcA.class.getName(),
					NfcB.class.getName(),
					NfcF.class.getName(),
					NfcV.class.getName(),
					IsoDep.class.getName(),
					MifareClassic.class.getName(),
					MifareUltralight.class.getName(), Ndef.class.getName()
			}
		};
	}
	
	public void enableBackgroundScan() {
		backgroundScan = true;
	}
	
	public void disableBackgroundScan() {
		backgroundScan = false;
	}	

	public void scanNFC(String gameObject, String methodName) {

		// Save callback object and method
		this.gameObject = gameObject;
		this.methodName = methodName;

		// No hardware
		if (mAdapter == null) {
			TellUnity("NO_HARDWARE");
			return;
		}
	}

	@Override
	public void onResume() {
		if (mAdapter != null) {
			mAdapter.enableForegroundDispatch(this, mPendingIntent, mFilters, mTechLists);
		}	  
		super.onResume();
	}

	@Override
	public void onPause() {
		if (mAdapter != null) {
			mAdapter.disableForegroundDispatch(this);
		}
		super.onPause();	
	}

	//response from the scan activity (not background scan mode)
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {           
		super.onActivityResult(requestCode, resultCode, data);

		if (requestCode == 0) {
			if (resultCode == RESULT_OK) {
				TellUnity(data.getStringExtra("SCAN_RESULT"));
			} else {
				TellUnity("CANCELLED");
			}
		}
	}
	
	//entry point when scanning (only to be used when on "background mode")
	@Override
	public void onNewIntent(Intent intent) {
		if (intent.getAction().equals(NfcAdapter.ACTION_TAG_DISCOVERED)) {
			TellUnity(ByteArrayToHexString(intent.getByteArrayExtra(NfcAdapter.EXTRA_ID)));
		}
	}

	private void TellUnity(String message) {
		UnityPlayer.UnitySendMessage(ScanActivity.this.gameObject, ScanActivity.this.methodName, message);
	}

	private String ByteArrayToHexString(byte [] inArray) {
		int i, j, in;
		String [] hex = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
		String out= "";

		for(j = 0 ; j < inArray.length ; ++j) {
			in = (int) inArray[j] & 0xff;
			i = (in >> 4) & 0x0f;
			out += hex[i];
			i = in & 0x0f;
			out += hex[i];
		}
		return out;
	}
}