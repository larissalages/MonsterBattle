package com.twinsprite.demokit.androidNFC;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NfcAdapter;
import android.nfc.tech.NfcF;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.RelativeLayout;
import android.nfc.tech.IsoDep;
import android.nfc.tech.MifareClassic;
import android.nfc.tech.MifareUltralight;
import android.nfc.tech.Ndef;
import android.nfc.tech.NfcA;
import android.nfc.tech.NfcB;
import android.nfc.tech.NfcV;

public class ScanNFCActivity extends Activity
{
	private NfcAdapter mAdapter = null;
	private PendingIntent mPendingIntent;
	private IntentFilter[] mFilters;
	private String[][] mTechLists;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Set full screen
		setTheme(android.R.style.Theme_NoTitleBar_Fullscreen);		
		getWindow().setFlags (WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

		// Get layout id
		int layoutID = getResources().getIdentifier("activity_scan_nfc", "layout", getPackageName());

		// Load layout
		RelativeLayout layout = (RelativeLayout) LayoutInflater.from(this).inflate(layoutID, null);

		// Set layout as content view
		setContentView(layout, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));

		// Create NFC Adapter
		mAdapter = NfcAdapter.getDefaultAdapter(this);

		if (mAdapter == null) {
			finishWithResult("NO_HARDWARE");
			return;
		}

		// Create a generic PendingIntent that will be deliver to this activity. The NFC stack
		// will fill in the intent with the details of the discovered tag before delivering to
		// this activity.
		mPendingIntent = PendingIntent.getActivity(this, 0,
				new Intent(this, ScanNFCActivity.class).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);

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

	@Override
	public void onNewIntent(Intent intent) {
		if (intent.getAction().equals(NfcAdapter.ACTION_TAG_DISCOVERED)) {
			finishWithResult(ByteArrayToHexString(intent.getByteArrayExtra(NfcAdapter.EXTRA_ID)));
		}
	}

	private void finishWithResult(String result) {
		Intent resultIntent = new Intent();
		resultIntent.putExtra("SCAN_RESULT", result);
		setResult(Activity.RESULT_OK, resultIntent);
		finish();
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
