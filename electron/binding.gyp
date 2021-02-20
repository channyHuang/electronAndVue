{
  "targets": [
    {
      "target_name": "ForNodeAddOn",
      "include_dirs": [
        "forNodeAddOn/includeDirs",
        "<!(node -e \"require('nan')\")"
      ],
      "sources": ["forNodeAddOn/nodeAddOnMain.cpp" ,
      "forNodeAddOn/managerAddOn.cpp"
      ],
      "win_delay_load_hook":"true"
    }
  ]
}

