using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class NFCController : MonoBehaviour
{
	public Text nfctext;

	void Start ()
	{
		AndroidNFCReader.enableBackgroundScan ();
		AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
	}

	void OnFinishScan (string result)
	{
		nfctext.text = "NFC Tag ID: " + result;
	}
}
