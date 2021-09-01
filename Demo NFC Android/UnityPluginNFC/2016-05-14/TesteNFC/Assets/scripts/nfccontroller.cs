using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class nfccontroller : MonoBehaviour
{
	public Text textNFC;

	void Start ()
	{
		AndroidNFCReader.enableBackgroundScan ();
		AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
	}

	void Update ()
	{
	
	}

	void OnFinishScan (string result)
	{
		// Cancelled
		if (result == AndroidNFCReader.CANCELLED)
			textNFC.text = "CANCELLED";

		// Error
		else if (result == AndroidNFCReader.ERROR) 
			textNFC.text = "ERROR";

		// No hardware
		else if (result == AndroidNFCReader.NO_HARDWARE)
			textNFC.text = "NO HARDWARE";

		textNFC.text = "HUHU";
	}

}
