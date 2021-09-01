using UnityEngine;
using System.Collections;

public class monsterviewercontroller : MonoBehaviour
{
	public int player;

	private battlecontroller battle_script;
	private SpriteRenderer sr;
	private monster m;
	private FieldPosition f;

	void Start ()
	{
		battle_script = GameObject.Find ("Battle Controller").GetComponent<battlecontroller> ();
		sr = GetComponent<SpriteRenderer> ();
		transform.localScale = new Vector3 (0.45f, 0.45f, 1f);
	}

	void Update ()
	{
		if (player == 1)
		{
			m = battle_script.GetCurrentMonster (1);
			f = battle_script.GetFieldPosition (1);

			if (f == FieldPosition.POSITION_DEFENSIVE) {
				transform.position = new Vector3 (-7.0f, 0.0f, 0.0f);
			} else if (f == FieldPosition.POSITION_NEUTRAL) {
				transform.position = new Vector3 (-4.35f, 0.0f, 0.0f);
			} else if (f == FieldPosition.POSITION_OFFENSIVE) {
				transform.position = new Vector3 (-2f, 0.0f, 0.0f);
			}
		}

		else
		{
			m = battle_script.GetCurrentMonster (2);
			f = battle_script.GetFieldPosition (2);

			if (f == FieldPosition.POSITION_DEFENSIVE) {
				transform.position = new Vector3 (7.0f, 0.0f, 0.0f);
			} else if (f == FieldPosition.POSITION_NEUTRAL) {
				transform.position = new Vector3 (4.35f, 0.0f, 0.0f);
			} else if (f == FieldPosition.POSITION_OFFENSIVE) {
				transform.position = new Vector3 (2f, 0.0f, 0.0f);
			}
		}

		//Seta o sprite do monstro
		if (m != null && m.GetCurrentHP () > 0) {
			sr.sprite = m.image;
		} else {
			sr.sprite = null;
		}
	}
}
