using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public enum MessageStyle { NORMAL, ERROR, REQUEST };

public class messageboardcontroller : MonoBehaviour
{
	public Text message_board_text;

	private string message;
	private MessageStyle messageStyle;

	private int fontSizeNormal;
	private int fontSizeRequest;
	private int fontSizeError;

	public void PushMessage(string message, MessageStyle messageStyle)
	{
		this.message = message;
		this.messageStyle = messageStyle;
	}

	void Start ()
	{
		message = "";
		messageStyle = MessageStyle.NORMAL;

		fontSizeNormal = 20;
		fontSizeError = 20;
		fontSizeRequest = 28;
	}

	void Update () 
	{
		message_board_text.text = message;

		if (messageStyle == MessageStyle.NORMAL)
		{
			message_board_text.color = Color.white;
			message_board_text.fontSize = fontSizeNormal;
		}

		else if (messageStyle == MessageStyle.ERROR)
		{
			message_board_text.color = new Color (1.0f, 155.0f/255.0f, 0.0f, 1.0f);
			message_board_text.fontSize = fontSizeError;
		}

		else if (messageStyle == MessageStyle.REQUEST)
		{
			message_board_text.color = Color.yellow;
			message_board_text.fontSize = fontSizeRequest;
		}
	}
}
