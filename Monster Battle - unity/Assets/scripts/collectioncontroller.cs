using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class collectioncontroller : MonoBehaviour 
{
	public GameObject readtagmsg;
	public GameObject monsterinfoui;

	public changescene fadeScript;
	public GameObject[] MONSTER_PREFABS;
	public Image image;
	public Text textname;
	public Text textdescription;
	public Text texttype;
	public Text texthp;
	public Text textatk;
	public Text textdef;
	public Text textspeed;

	private monster current_monster;

	void Start ()
	{
		//Impede a tela do celular de suspender
		Screen.sleepTimeout = SleepTimeout.NeverSleep;

		AndroidNFCReader.enableBackgroundScan ();
		AndroidNFCReader.ScanNFC (gameObject.name, "OnFinishScan");
		current_monster = null;
	}

	void OnFinishScan (string result)
	{
		int monster_id = monster.GetMonsterIDFromTag (result);

		if (monster_id != -1) 
			current_monster = MONSTER_PREFABS [monster_id-1].GetComponent<monster>();
	}

	void KeyboardInput()
	{
		if (Input.GetKeyDown (KeyCode.Alpha1))
			current_monster = MONSTER_PREFABS [0].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha2))
			current_monster = MONSTER_PREFABS [1].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha3))
			current_monster = MONSTER_PREFABS [2].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha4))
			current_monster = MONSTER_PREFABS [3].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha5))
			current_monster = MONSTER_PREFABS [4].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha6))
			current_monster = MONSTER_PREFABS [5].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha7))
			current_monster = MONSTER_PREFABS [6].GetComponent<monster>();
		else if (Input.GetKeyDown (KeyCode.Alpha8))
			current_monster = MONSTER_PREFABS [7].GetComponent<monster>();
	}

	void Update()
	{
		//Se apertar esc ou botão de voltar no cel
		if (Input.GetKeyDown (KeyCode.Escape)) 
		{
			fadeScript.ChangeScene ("menu3");
			gameObject.SetActive (false);
		}

		//Se usar as teclas também funciona
		KeyboardInput ();

		if (current_monster != null)
		{
			readtagmsg.SetActive (false);
			monsterinfoui.SetActive (true);

			image.sprite = current_monster.image;
			textname.text = current_monster.uiname;
			textdescription.text = current_monster.description;
			texttype.text = gametype.GetString (current_monster.type);
			texthp.text = "HP -> " + current_monster.hp.ToString ();
			textatk.text = "Attack -> " + current_monster.attack.ToString ();
			textdef.text = "Defense -> " + current_monster.defense.ToString ();
			textspeed.text = "Speed -> " + current_monster.speed.ToString ();
		} 

		else
		{
			readtagmsg.SetActive (true);
			monsterinfoui.SetActive (false);
		}
	}
}
