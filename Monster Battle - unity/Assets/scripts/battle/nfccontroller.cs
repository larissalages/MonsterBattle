using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class nfccontroller : MonoBehaviour
{
	private string current_tag;
	private string last_tag;

	void Start ()
	{
		AndroidNFCReader.enableBackgroundScan ();
		AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
		current_tag = "";
		last_tag = "";
	}
		
	void OnFinishScan (string result)
	{
		current_tag = result;
		last_tag = result;
	}

	public string GetLastTagRead()
	{
		return last_tag;
	}

	int hardcoded;
	public int GetMonsterFromNFC()
	{
		int monster_id = monster.GetMonsterIDFromTag(current_tag);
		current_tag = "";

		return monster_id;
	}

	public int GetCardFromNFC()
	{
		int card_id = card.GetCardIDFromTag (current_tag);
		current_tag = "";

		return card_id;
	}
}
