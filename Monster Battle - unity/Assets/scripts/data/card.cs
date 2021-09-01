using UnityEngine;
using System.Collections;

public class card : MonoBehaviour
{
	public string uiname;
	public int power;
	public int accuracy;
	public int cooldown;
	public GameType type;

	public static int GetCardIDFromTag(string tag)
	{
		int card_id = -1;

		if (tag == "041DC4220A4080" || tag == "04F99C5ABB2B80") //SWAP
			card_id = 0;
		else if (tag == "0432C4220A4080" || tag == "0422C3220A4080") //AFTERSHOCK
			card_id = 1;
		else if (tag == "045F9D5ABB2B80" || tag == "04129C5ABB2B81") //SEISMIC BREAK
			card_id = 2;
		else if (tag == "04479D5ABB2B80" || tag == "04119D5ABB2B81") //INUNDATION
			card_id = 3;
		else if (tag == "042F9D5ABB2B80" || tag == "04119C5ABB2B81") //TIDAL WAVE
			card_id = 4;
		else if (tag == "041EC4220A4080" || tag == "047A9D5ABB2B80") //SKY DIVING 
			card_id = 5;
		else if (tag == "04109D5ABB2B81" || tag == "04DE9D5ABB2B80") //TYPHOON
			card_id = 6;
		else if (tag == "04609D5ABB2B80" || tag == "0437C3220A4080") //NATURE FORCE
			card_id = 7;
		else if (tag == "04939D5ABB2B80" || tag == "04F69D5ABB2B80") //STORM OF SPIRITS
			card_id = 8;

		return card_id;
	}
}