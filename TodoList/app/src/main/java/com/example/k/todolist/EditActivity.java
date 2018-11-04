package com.example.k.todolist;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class EditActivity extends AppCompatActivity {

    private EditText editText;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit);
        editText = (EditText) findViewById(R.id.edit_text);
        Intent intent = getIntent();
        String intentdata = intent.getStringExtra("extra_data");
        editText.setText(intentdata);
        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String inputText = editText.getText().toString();
                if(inputText==null)inputText="";
                Intent intent = new Intent();
                intent.putExtra("data_return",inputText);
                setResult(RESULT_OK,intent);
                finish();
            }
        });
    }
}
