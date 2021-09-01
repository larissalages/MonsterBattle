using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class debuginfocontroller : MonoBehaviour
{
	public nfccontroller nfc_controller;
	public Text text_tag_id;
	private int current_number;

	void Start ()
	{
		current_number = -1;
	}

	void Update ()
	{
		text_tag_id.text = nfc_controller.GetLastTagRead ();
	}

	public void SetCurrentNumber(int number)
	{
		current_number = number;
	}

	public int GetMonsterFromKeypad()
	{
		int id = -1;
		
		if (current_number > 0)
		{
			id = current_number;
			current_number = -1;
		}

		return id;
	}

	public int GetCardFromKeypad()
	{
		int id = -1;

		if (current_number >= 0)
		{
			id = current_number;
			current_number = -1;
		}

		return id;
	}
}
