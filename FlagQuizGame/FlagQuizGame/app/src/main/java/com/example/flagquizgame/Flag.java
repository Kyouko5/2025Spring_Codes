// Flag.java
package com.example.flagquizgame;

/**
 * 数据模型类，用于存储国旗图片资源 ID 和对应的国家名称
 */
public class Flag {
    private int imageResId;      // 国旗图片的资源 ID
    private String countryName;  // 国家名称

    public Flag(int imageResId, String countryName) {
        this.imageResId = imageResId;
        this.countryName = countryName;
    }

    public int getImageResId() {
        return imageResId;
    }

    public String getCountryName() {
        return countryName;
    }
}