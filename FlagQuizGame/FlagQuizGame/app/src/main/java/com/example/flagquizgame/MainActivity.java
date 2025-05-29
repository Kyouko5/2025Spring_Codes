/*
 * @Author: Kyouko
 * @Date: 2025-03-25 17:15:45
 * @LastEditTime: 2025-05-13 08:31:51
 * @Description: 请输入文件描述
 * @FilePath: /FlagQuizGame/app/src/main/java/com/example/flagquizgame/MainActivity.java
 */
// MainActivity.java
package com.example.flagquizgame;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.List;

/**
 * 主界面，负责显示国旗图片和选项，处理用户选择
 */
public class MainActivity extends AppCompatActivity {
    private ImageView flagImageView;       // 显示国旗图片
    private Button[] optionButtons;        // 选项按钮数组
    private TextView questionNumberTextView; // 显示题目序号
    private int currentQuestion = 0;       // 当前题目序号
    private int correctAnswers = 0;        // 猜对的次数
    private int totalGuesses = 0;          // 总猜测次数
    private Flag currentFlag;              // 当前题目对应的国旗
    private List<String> currentOptions;   // 当前题目的选项列表

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 初始化界面元素
        flagImageView = findViewById(R.id.flagImageView);
        optionButtons = new Button[]{
                findViewById(R.id.optionButton1),
                findViewById(R.id.optionButton2),
                findViewById(R.id.optionButton3),
                findViewById(R.id.optionButton4)
        };
        questionNumberTextView = findViewById(R.id.questionNumberTextView);

        // 开始第一道题目
        startNewQuestion();
    }

    /**
     * 开始新的一道题目，更新界面内容
     */
    private void startNewQuestion() {
        if (currentQuestion < 10) { // 每轮游戏有 10 道题目
            currentQuestion++;
            questionNumberTextView.setText("题目 " + currentQuestion + " / 10");
            currentFlag = Utils.getRandomFlag();           // 随机选择国旗
            currentOptions = Utils.getRandomOptions(currentFlag, 4); // 生成 4 个选项

            // 更新界面
            flagImageView.setImageResource(currentFlag.getImageResId());
            for (int i = 0; i < optionButtons.length; i++) {
                optionButtons[i].setText(currentOptions.get(i));
                optionButtons[i].setEnabled(true);          // 启用按钮
                optionButtons[i].setBackgroundColor(getResources().getColor(android.R.color.white)); // 重置颜色
            }
        } else {
            // 10 道题目完成后，跳转到结果界面
            Intent intent = new Intent(this, ResultActivity.class);
            intent.putExtra("correctAnswers", correctAnswers);
            intent.putExtra("totalGuesses", totalGuesses);
            startActivity(intent);
            finish();
        }
    }

    /**
     * 处理用户点击选项按钮的事件
     * @param view 被点击的按钮
     */
    public void onOptionClick(View view) {
        Button clickedButton = (Button) view;
        String selectedOption = clickedButton.getText().toString();
        totalGuesses++; // 每次选择增加猜测次数

        if (selectedOption.equals(currentFlag.getCountryName())) {
            // 选择正确
            correctAnswers++;
            Toast.makeText(this, "恭喜你，答对了！", Toast.LENGTH_SHORT).show();
            startNewQuestion(); // 进入下一题
        } else {
            // 选择错误
            clickedButton.setEnabled(false); // 禁用错误选项
            clickedButton.setBackgroundColor(getResources().getColor(android.R.color.darker_gray)); // 变色
            Toast.makeText(this, "答错了，再试一次！", Toast.LENGTH_SHORT).show();
        }
    }
}