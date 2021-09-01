using UnityEngine;
// using UnityEngine.UI;
using System.Collections;

public class NFCExample : MonoBehaviour
{
    // public GUIText tag_output_text;
    // AndroidJavaClass pluginTutorialActivityJavaClass;

	string qrString = "";
	bool background = true;
	
    void Start ()
    {
        // AndroidJNI.AttachCurrentThread ();
        // pluginTutorialActivityJavaClass = new AndroidJavaClass ("com.twinsprite.demokit.androidNFC");
		
		AndroidNFCReader.enableBackgroundScan ();
		AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
    }
    
    void Update ()
    {
        //string value = pluginTutorialActivityJavaClass.CallStatic<string> ("getValue");
        //tag_output_text.text = "Value:\n" + value;
    }

	void OnGUI ()
	{
		if (!background) {
			// Scan NFC button
			if (GUI.Button (new Rect (0, Screen.height - 50, Screen.width, 50), "Scan NFC")) {
				AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
			}
			if (GUI.Button (new Rect (0, Screen.height - 100, Screen.width, 50), "Enable Backgraound Mode")) {
				AndroidNFCReader.enableBackgroundScan ();
				background = true;
			}
		}else{
			if (GUI.Button (new Rect (0, Screen.height - 50, Screen.width, 50), "Disable Backgraound Mode")) {
				AndroidNFCReader.disableBackgroundScan ();
				background = false;
			}
		}
		GUI.Label (new Rect (0, 0, Screen.width, 50), "Result: " + qrString);
	}

	void OnFinishScan (string result)
	{
		// Cancelled
		if (result == AndroidNFCReader.CANCELLED)
			qrString = "CANCELLED";

		// Error
		else if (result == AndroidNFCReader.ERROR) 
			qrString = "ERROR";

		// No hardware
		else if (result == AndroidNFCReader.NO_HARDWARE)
			qrString = "NO HARDWARE";

		//tag_output_text.text = "HUHU";
		qrString = result;
	}
}
