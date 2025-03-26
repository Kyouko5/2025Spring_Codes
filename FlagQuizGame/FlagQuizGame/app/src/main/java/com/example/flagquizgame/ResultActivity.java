// ResultActivity.java
package com.example.flagquizgame;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

/**
 * 结果界面，显示游戏结果并提供继续或退出选项
 */
public class ResultActivity extends AppCompatActivity {
    private TextView resultTextView;   // 显示结果
    private Button continueButton;     // 继续游戏按钮
    private Button exitButton;         // 退出按钮

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);

        // 初始化界面元素
        resultTextView = findViewById(R.id.resultTextView);
        continueButton = findViewById(R.id.continueButton);
        exitButton = findViewById(R.id.exitButton);

        // 获取游戏数据
        int correctAnswers = getIntent().getIntExtra("correctAnswers", 0);
        int totalGuesses = getIntent().getIntExtra("totalGuesses", 0);
        double accuracy = (double) correctAnswers / 10 * 100; // 计算正确率

        // 显示结果
        resultTextView.setText("你猜对了 " + correctAnswers + " / 10 题。\n" +
                "总猜测次数: " + totalGuesses + "\n" +
                "正确率: " + String.format("%.1f", accuracy) + "%");

        // 继续游戏按钮点击事件
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ResultActivity.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
        });

        // 退出按钮点击事件
        exitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish(); // 退出应用
            }
        });
    }
}