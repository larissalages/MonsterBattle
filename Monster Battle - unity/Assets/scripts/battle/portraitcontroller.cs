using UnityEngine;
using System.Collections;

public class portraitcontroller : MonoBehaviour
{
	public int player;
	public GameObject portrait_prefab;

	private battlecontroller battle_script;
	private int TEAM_SIZE;
	private GameObject[] portraits1;
	private GameObject[] portraits2;

	void Start ()
	{
		battle_script = GameObject.Find ("Battle Controller").GetComponent<battlecontroller> ();
		TEAM_SIZE = 2;//battle_script.GetTeamSize ();
		portraits1 = new GameObject[TEAM_SIZE];
		portraits2 = new GameObject[TEAM_SIZE];

		//Instancia os portraits e posiciona e desabilita sprites
		for (int i = 0; i < TEAM_SIZE; i++)
		{
			if (player == 1) 
			{
				portraits1 [i] = (GameObject)Instantiate (portrait_prefab);
				portraits1 [i].transform.position = new Vector3 (-7.5f + 0.9f * i, 4.5f, 0.0f);
				portraits1 [i].transform.GetChild (1).gameObject.SetActive (false);
				portraits1 [i].transform.GetChild (2).gameObject.SetActive (false);
				portraits1 [i].transform.GetChild (3).gameObject.SetActive (false);
			} 

			else if (player == 2)
			{
				portraits2 [i] = (GameObject)Instantiate (portrait_prefab);
				portraits2 [i].transform.position = new Vector3 (7.5f - 0.9f * i, -4.5f, 0.0f);
				portraits2 [i].transform.GetChild (1).gameObject.SetActive (false);
				portraits2 [i].transform.GetChild (2).gameObject.SetActive (false);
				portraits2 [i].transform.GetChild (3).gameObject.SetActive (false);
			}
		}
	}

	void Update ()
	{
		//Percorre time e seta imagem correta
		for (int i = 0; i < TEAM_SIZE; i++)
		{
			monster m = battle_script.GetMonster (player, i);

			if (player == 1 && m != null)
			{	
				portraits1 [i].transform.GetChild (1).gameObject.SetActive (true);
				portraits1 [i].transform.GetChild (2).gameObject.SetActive (true);
				portraits1 [i].transform.GetChild (2).gameObject.GetComponent<SpriteRenderer> ().sprite = m.portrait;
				if(m.GetCurrentHP() <= 0)
					portraits1 [i].transform.GetChild (3).gameObject.SetActive (true); // coloca o x
			}

			else if (player == 2 && m != null)
			{	
				portraits2 [i].transform.GetChild (1).gameObject.SetActive (true);
				portraits2 [i].transform.GetChild (2).gameObject.SetActive (true);
				portraits2 [i].transform.GetChild (2).gameObject.GetComponent<SpriteRenderer> ().flipX = true; //ativa o flip
				portraits2 [i].transform.GetChild (2).gameObject.GetComponent<SpriteRenderer> ().sprite = m.portrait;
				if(m.GetCurrentHP() <= 0)
					portraits2 [i].transform.GetChild (3).gameObject.SetActive (true); // coloca o x
			}
		}
	}
}
