using UnityEngine;
using System.Collections;

public class scrollbackground : MonoBehaviour
{
	public SpriteRenderer sr1;
	public SpriteRenderer sr2;
	public float speed;

	private Vector3 initial_pos1;
	private Vector3 initial_pos2;

	void Start ()
	{
		initial_pos1 = sr1.transform.position;
		initial_pos2 = sr2.transform.position;
	}

	void Update ()
	{
		Vector3 pos1 = sr1.transform.position;
		Vector3 pos2 = sr2.transform.position;

		pos1.x = pos1.x - speed * Time.deltaTime;
		pos2.x = pos2.x - speed * Time.deltaTime;

		if (pos2.x <= 0.0f)
		{
			pos1 = initial_pos1;
			pos2 = initial_pos2;
		}

		sr1.transform.position = pos1;
		sr2.transform.position = pos2;
	}
}
