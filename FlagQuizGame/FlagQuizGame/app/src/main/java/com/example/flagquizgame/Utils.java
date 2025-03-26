// Utils.java
package com.example.flagquizgame;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

/**
 * 工具类，提供随机选择国旗和选项的功能
 */
public class Utils {
    private static List<Flag> flags = new ArrayList<>(); // 国旗列表
    private static Random random = new Random();         // 随机数生成器

    // 静态初始化块，加载国旗 specialty，使用国家代码作为资源 ID
    static {
        // 示例：添加一些常见国家的国旗
        flags.add(new Flag(R.drawable.cn, "China"));       // 中国
        flags.add(new Flag(R.drawable.us, "United States")); // 美国
        flags.add(new Flag(R.drawable.br, "Brazil"));      // 巴西
        flags.add(new Flag(R.drawable.jp, "Japan"));       // 日本
        flags.add(new Flag(R.drawable.gb, "United Kingdom")); // 英国
        flags.add(new Flag(R.drawable.fr, "France"));      // 法国
        flags.add(new Flag(R.drawable.de, "Germany"));     // 德国
        flags.add(new Flag(R.drawable.in, "India"));       // 印度
        flags.add(new Flag(R.drawable.ru, "Russia"));      // 俄罗斯
        flags.add(new Flag(R.drawable.au, "Australia"));   // 澳大利亚
        flags.add(new Flag(R.drawable.ca, "Canada"));         // 加拿大
        flags.add(new Flag(R.drawable.it, "Italy"));          // 意大利
        flags.add(new Flag(R.drawable.es, "Spain"));          // 西班牙
        flags.add(new Flag(R.drawable.mx, "Mexico"));         // 墨西哥
        flags.add(new Flag(R.drawable.kr, "South Korea"));    // 韩国
        flags.add(new Flag(R.drawable.za, "South Africa"));   // 南非
        flags.add(new Flag(R.drawable.ar, "Argentina"));      // 阿根廷
        flags.add(new Flag(R.drawable.tr, "Turkey"));         // 土耳其
        flags.add(new Flag(R.drawable.eg, "Egypt"));          // 埃及
        flags.add(new Flag(R.drawable.id, "Indonesia"));      // 印尼
        flags.add(new Flag(R.drawable.sa, "Saudi Arabia"));   // 沙特阿拉伯
        flags.add(new Flag(R.drawable.ng, "Nigeria"));        // 尼日利亚
        flags.add(new Flag(R.drawable.th, "Thailand"));       // 泰国
        flags.add(new Flag(R.drawable.se, "Sweden"));         // 瑞典
        flags.add(new Flag(R.drawable.no, "Norway"));         // 挪威
        flags.add(new Flag(R.drawable.ch, "Switzerland"));    // 瑞士
        flags.add(new Flag(R.drawable.nl, "Netherlands"));    // 荷兰
        flags.add(new Flag(R.drawable.pl, "Poland"));         // 波兰
        flags.add(new Flag(R.drawable.vn, "Vietnam"));        // 越南
        flags.add(new Flag(R.drawable.ph, "Philippines"));    // 菲律宾
        // 你可以继续添加更多国家，例如：
        // flags.add(new Flag(R.drawable.ca, "Canada"));
        // flags.add(new Flag(R.drawable.it, "Italy"));
        // flags.add(new Flag(R.drawable.es, "Spain"));
        // 根据需要扩展完整列表
    }

    /**
     * 从国旗列表中随机选择一个国旗
     * @return 随机选择的 Flag 对象
     */
    public static Flag getRandomFlag() {
        return flags.get(random.nextInt(flags.size()));
    }

    /**
     * 生成包含正确答案的随机选项列表
     * @param correctFlag 正确答案的 Flag 对象
     * @param optionCount 选项总数（包括正确答案）
     * @return 随机排列的选项列表
     */
    public static List<String> getRandomOptions(Flag correctFlag, int optionCount) {
        List<String> options = new ArrayList<>();
        options.add(correctFlag.getCountryName()); // 添加正确答案

        // 添加错误答案，直到达到指定选项数量
        while (options.size() < optionCount) {
            Flag randomFlag = getRandomFlag();
            String countryName = randomFlag.getCountryName();
            if (!options.contains(countryName)) { // 避免重复
                options.add(countryName);
            }
        }

        Collections.shuffle(options); // 随机打乱选项顺序
        return options;
    }
}