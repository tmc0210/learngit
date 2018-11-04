package com.example.k.todolist;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;


public class MainActivity extends AppCompatActivity {


    public int dataPosition;
    public ArrayList<String> data = new ArrayList<>(Arrays.asList("1", "2", "3", "4", ""));
    public void saveArrayList(Context context, ArrayList searchList, String content) {
        if (searchList.size() == 0) {
            searchList.add(content + "");
        } else {
            if (!searchList.contains(content)) {
                searchList.add(0, content + "");
            } else {
                for (int i = 0; i < searchList.size(); i++) {
                    if (searchList.get(i).equals(content)) {
                        searchList.remove(i);
                        searchList.add(0, content + "");
                    }
                }
            }
        }
        SharedPreferences.Editor editor = context.getSharedPreferences(
                "SearchDataList", context.MODE_PRIVATE).edit();
        editor.putInt("searchNums", searchList.size());
        for (int i = 0; i < searchList.size(); i++) {
            editor.putString("item_" + i, searchList.get(i) + "");
        }
        editor.commit();
    }


    public ArrayList<String> getSearchArrayList(Context context) {
        SharedPreferences preferDataList = context.getSharedPreferences(
                "SearchDataList", context.MODE_PRIVATE);
        ArrayList<String> list = new ArrayList<>();
        int searchNums = preferDataList.getInt("searchNums", 0);
        for (int i = 0; i < searchNums; i++) {
            String searchItem = preferDataList.getString("item_" + i, null);
            list.add(searchItem);
        }
        return list;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        saveArrayList(MainActivity.this, data,"NEXT_DATA" );
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent intentdata) {
        switch (requestCode) {
            case 1:
                if (resultCode == RESULT_OK) {
                    String returnedData = intentdata.getStringExtra("data_return");
                    data.set(dataPosition, returnedData);
                    if (dataPosition == data.size() - 1)
                        data.add("");
                }
                break;
            default:
        }

    }

    @Override
    protected void onResume() {
        super.onResume();
        ArrayAdapter<String> startAdapter = new ArrayAdapter<String>(
                MainActivity.this, android.R.layout.simple_list_item_1, data);
        final ListView listView = (ListView) findViewById(R.id.list_view);
        listView.setAdapter(startAdapter);
        if(data.get(0).equals("NEXT_DATA"))data.remove(0);
        startAdapter.notifyDataSetChanged();
        listView.invalidate();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if(getSearchArrayList(MainActivity.this).size()!=0)data=getSearchArrayList(MainActivity.this);
        final ArrayAdapter<String> adapter = new ArrayAdapter<String>(
                MainActivity.this, android.R.layout.simple_list_item_1, data);
        final ListView listView = (ListView) findViewById(R.id.list_view);
        listView.setAdapter(adapter);
        adapter.notifyDataSetChanged();
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(MainActivity.this, EditActivity.class);
                intent.putExtra("extra_data", data.get(position));
                dataPosition = position;
                startActivityForResult(intent, 1);
            }
        });
        listView.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view,  int longClickPosition, long id) {
                if(data.remove((int)longClickPosition)!=null) {
                    System.out.println("success");
                }
                if (longClickPosition == data.size())
                     data.add("");
                onResume();
                return true;
            }
        });
    }
}