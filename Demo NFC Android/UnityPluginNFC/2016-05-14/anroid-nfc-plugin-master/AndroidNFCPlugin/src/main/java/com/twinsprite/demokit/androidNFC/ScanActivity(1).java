package com.twinsprite.demokit.androidNFC;

import java.nio.charset.Charset;
import java.util.Arrays;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentFilter.MalformedMimeTypeException;
import android.net.Uri;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.tech.NfcF;
import android.os.Bundle;
import android.os.Parcelable;

// copy&paste
import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.tech.IsoDep;
import android.nfc.tech.MifareClassic;
import android.nfc.tech.MifareUltralight;
import android.nfc.tech.Ndef;
import android.nfc.tech.NfcA;
import android.nfc.tech.NfcB;
import android.nfc.tech.NfcF;
import android.nfc.tech.NfcV;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;


import com.unity3d.player.UnityPlayer;
import com.unity3d.player.UnityPlayerActivity;

public class ScanActivity extends UnityPlayerActivity {

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
	
	public void enableBackgroundScan()
	{
		backgroundScan = true;
	}
	
	public void disableBackgroundScan()
	{
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

		if (!backgroundScan)
		{
			//not background scan, launch the scan activity
			runOnUiThread(new Runnable() {
	
				@Override
				public void run() {
					Intent intent = new Intent(ScanActivity.this,ScanNFCActivity.class);					
					startActivityForResult(intent, 0);
				}
			});
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
			TellUnity("NFC Tag\n" + ByteArrayToHexString(intent.getByteArrayExtra(NfcAdapter.EXTRA_ID)));
		}
	}

	private String ByteArrayToHexString(byte [] inarray) {
		int i, j, in;
		String [] hex = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
		String out= "";

		for(j = 0 ; j < inarray.length ; ++j)
		{
			in = (int) inarray[j] & 0xff;
			i = (in >> 4) & 0x0f;
			out += hex[i];
			i = in & 0x0f;
			out += hex[i];
		}
		return out;
	}

	/*
	public void onNewIntent(Intent intent) {
		super.onNewIntent(intent);

		//if not waiting for background scan, ignore
		if (!backgroundScan)
			return;
		
		String nfcText = "";

		Parcelable[] ndefMessages = (Parcelable[])(intent.getParcelableArrayExtra("android.nfc.extra.NDEF_MESSAGES"));
		if (ndefMessages != null)
		{			
			try
			{
				for(int i = 0; i < ndefMessages.length; i++)
				{        			
					NdefMessage ndefMessage = (NdefMessage)(ndefMessages[i]);	            
					NdefRecord[] ndefRecords = ndefMessage.getRecords();

					for (int j = 0; j < ndefRecords.length; j++) {					      		
						if (ndefRecords[j].getTnf() == NdefRecord.TNF_WELL_KNOWN && 
								Arrays.equals(ndefRecords[j].getType(), NdefRecord.RTD_TEXT)) {	

							byte[] payLoad = ndefRecords[0].getPayload();

							//Get the Text Encoding
							String textEncoding = ((payLoad[0] & 0200) == 0) ? "UTF-8" : "UTF-16";

							//Get the Language Code
							int languageCodeLength = payLoad[0] & 0077;
							//String languageCode = new String(payLoad, 1, languageCodeLength, "US-ASCII");

							//Get the Text
							nfcText = new String(payLoad, languageCodeLength + 1, payLoad.length - languageCodeLength - 1, textEncoding);


						}
						else if (ndefRecords[j].getTnf() == NdefRecord.TNF_WELL_KNOWN && 
								Arrays.equals(ndefRecords[j].getType(), NdefRecord.RTD_URI)) {

							byte[] payload = ndefRecords[j].getPayload();
							String prefix = (String) URI_PREFIX_MAP[payload[0]];

							byte prefBytes[] = prefix.getBytes(Charset.forName("UTF-8"));
							byte postBytes[] = Arrays.copyOfRange(payload, 1, payload.length);

							byte[] fullUri = new byte[prefBytes.length + postBytes.length];
							System.arraycopy(prefBytes, 0, fullUri, 0, prefBytes.length);
							System.arraycopy(postBytes, 0, fullUri, prefBytes.length, postBytes.length);

							nfcText= new String(fullUri, Charset.forName("UTF-8"));
						}
					}
				}      
			}
			catch (Exception e){
				TellUnity("ERROR");
				return;
			}        
		}

		// Scan completed
		TellUnity(nfcText);
		
	}
	*/
	
	private void TellUnity(String message)
	{
		UnityPlayer.UnitySendMessage(ScanActivity.this.gameObject, ScanActivity.this.methodName, message);
	}

}