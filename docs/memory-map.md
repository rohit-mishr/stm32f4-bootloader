\# Flash Memory Map (STM32F446RE - 512KB)



The asymmetric sectors are partitioned to support the Bootloader, Application, Non-Volatile Storage, and future OTA capabilities.



| Sector | Size | Address Start | Purpose |

| :--- | :--- | :--- | :--- |

| \*\*0\*\* | 16 KB | `0x0800 0000` | \*\*Bootloader:\*\* Hardware init, signature validation, VTOR jump. |

| \*\*1\*\* | 16 KB | `0x0800 4000` | \*\*Configuration:\*\* Node ID, thresholds, boot count (wear-leveled). |

| \*\*2\*\* | 16 KB | `0x0800 8000` | \*\*Application (Start):\*\* Vector table and main application code. |

| \*\*3\*\* | 16 KB | `0x0800 C000` | \*\*Application\*\* |

| \*\*4\*\* | 64 KB | `0x0801 0000` | \*\*Application\*\* |

| \*\*5\*\* | 128 KB| `0x0802 0000` | \*\*Application\*\* |

| \*\*6\*\* | 128 KB| `0x0804 0000` | \*\*Event Log:\*\* Circular buffer for offline alarms. |

| \*\*7\*\* | 128 KB| `0x0806 0000` | \*\*Reserved / Future OTA:\*\* Staging area for firmware updates. |



\*Note: Application spans Sectors 2, 3, 4, and 5 (Total 224 KB).\*

