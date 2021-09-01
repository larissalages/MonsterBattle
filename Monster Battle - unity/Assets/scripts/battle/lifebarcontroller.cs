using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class lifebarcontroller : MonoBehaviour
{
	public int player;

	private battlecontroller battle_script;
	private Text texthp;
	private Text textname;
	private GameObject bar;
	private GameObject frame;

	void Start ()
	{
		battle_script = GameObject.Find ("Battle Controller").GetComponent<battlecontroller> ();
		frame = transform.GetChild (0).gameObject;
		bar = transform.GetChild (1).gameObject;
		textname = transform.GetChild (2).gameObject.GetComponent<Text>();
		texthp = transform.GetChild (3).gameObject.GetComponent<Text>();
	}

	void Update ()
	{
		monster m = battle_script.GetCurrentMonster (player);

		if (m != null && m.GetCurrentHP() > 0)
		{
			bar.SetActive (true);
			frame.SetActive (true);
			bar.GetComponent<Image> ().fillAmount = m.GetHPProportion ();
			texthp.text = m.GetCurrentHP().ToString();
			textname.text = m.uiname;

			//Tint sprite
			if (m.GetHPProportion () <= 0.3f) //Life crítico
				bar.GetComponent<Image> ().color = new Color (1f, 0f, 0f, 1f);
			else if(m.GetHPProportion () <= 0.7f) //Life médio
				bar.GetComponent<Image> ().color = new Color (1f, 0.72f, 0f, 1f);
			else 								//Life bom
				bar.GetComponent<Image> ().color = new Color (0.36f, 1f, 0f, 1f);
		} 

		else
		{
			bar.SetActive (false);
			frame.SetActive (false);
			texthp.text = "";
			textname.text = "";
		}
	}
}
